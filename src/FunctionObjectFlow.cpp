#include "FunctionObjectFlow.h"

#include <queue>

#include "ConstraintSolver.h"
#include "Utils.h"

static bool isConstructor(string functionName) {
    if (functionName.substr(functionName.length() - 2) != "()") return false;
    functionName = functionName.substr(0, functionName.length() - 2);
    auto pos = functionName.find("::");
    if (pos == string::npos) return false;
    string left = functionName.substr(0, pos);
    string right = functionName.substr(pos + 2);
    return left == right;
}

static string getConstructorClassName(string functionName) {
    functionName = functionName.substr(0, functionName.length() - 2);
    auto pos = functionName.find("::");
    string left = functionName.substr(0, pos);
    string right = functionName.substr(pos + 2);
    return right;
}

void FunctionObjectFlow::addInstantiation(const Value *dst, const string &className) {
    auto it = instantiations.find(dst);
    if (it == instantiations.end()) {
        it = instantiations.insert({dst, set<string>()}).first;
    }
    it->second.insert(className);
}

void FunctionObjectFlow::handleCallBase(const Instruction *inst) {
    const auto *callBase = dyn_cast<CallBase>(inst);
    // outs() << "CALL/INVOKE " << inst << " <- " << callBase->getOperand(0) << '\n';
    bool constructor = false;
    bool system = false;
    if (inst->getType()->isPointerTy() && inst->getType()->getPointerElementType()->isStructTy()) {
        auto ty = inst->getType()->getPointerElementType();
        string className = stripClassName(ty->getStructName().str());
        if (classes->isClassExist(className)) {
            constraintSystem.addLiteralConstraint(
                dyn_cast<Value>(inst),
                classes->getHierarchyGraph().querySelfWithDerivedClasses(className),
                ConstraintRelation::Superset);
        }
    }
    if (auto callee = callBase->getCalledFunction()) {
        string demangled = demangle(callee->getName().str());
        // outs() << "     (" << demangled << ")\n";
        if (isConstructor(demangled)) {
            // outs() << "constructor of " << getConstructorClassName(demangled) << " in function "
            //        << demangle(function->getName().str()) << " in "
            //        << function->getParent()->getName() << '\n';
            constructor = true;
            // outs() << "     [ CONSTRUCTOR ]\n";
            addInstantiation(callBase->getOperand(0), getConstructorClassName(demangled));
        }
        if (beginsWith(demangled, "operator new") || beginsWith(demangled, "llvm.memset")) {
            // outs() << "operator new() in function " << demangle(function->getName().str()) <<
            // " in " << function->getParent()->getName() << '\n';
            system = true;
        }
    }
    if (!constructor && !system) {
        // outs() << "adding " << inst << " to ret val set: " << *inst << '\n';
        retVals.insert(inst);
    }
}

void FunctionObjectFlow::analyzeFunction(const Function *f) {
    function = f;

    auto isPolymorphicType = [this](const Value *v) -> bool {
        if (!v->getType()->isPointerTy()) {
            return false;
        }
        auto ty = v->getType()->getPointerElementType();
        if (!ty->isStructTy()) {
            return false;
        }
        auto tyName = stripClassName(ty->getStructName().str());
        if (!classes->isClassExist(tyName)) {
            return false;
        }
        return true;
    };

    auto derivedClassesOf = [this](const Value *v) -> set<string> {
        auto ty = v->getType()->getPointerElementType();
        auto tyName = stripClassName(ty->getStructName().str());
        return classes->getHierarchyGraph().querySelfWithDerivedClasses(tyName);
    };

    auto constrainNominalType = [=](const Value *v) {
        if (isPolymorphicType(v)) {
            auto set = derivedClassesOf(v);
            // outs() << "constrain (" << v << ") [" << *v << "] to {" << list_out(set) << "}\n";
            constraintSystem.addLiteralConstraint(v, set);
        }
    };

    for (size_t i = 0; i < f->arg_size(); i++) {
        const Argument *arg = f->getArg(i);
        arguments.emplace_back(arg);
        constrainNominalType(arg);
    }

    for (auto &bb : *f) {
        for (auto &inst : bb) {
            // outs() << "Processing " << inst << '\n';
            switch (inst.getOpcode()) {
                case Instruction::Alloca: {
                    alloca.insert(&inst);
                    constrainNominalType(&inst);
                    // outs() << "ALLOCA " << &inst << '\n';
                    break;
                }
                case Instruction::Load: {
                    if (inst.getType()->isPointerTy()) {
                        constraintSystem.addConstraint(inst.getOperand(0), &inst);
                        // addEdge(inst.getOperand(0), &inst, ConstraintType::Widen);
                        // outs() << "LOAD " << &inst << " <- " << inst.getOperand(0) << '\n';
                    }
                    constrainNominalType(&inst);
                    break;
                }
                case Instruction::Store: {
                    if (inst.getOperand(0)->getType()->isPointerTy() &&
                        !isa<ConstantPointerNull>(inst.getOperand(0))) {
                        constraintSystem.addConstraint(inst.getOperand(0), inst.getOperand(1));
                        // addEdge(inst.getOperand(0), inst.getOperand(1), ConstraintType::Widen);
                        // outs() << "STORE " << inst.getOperand(1) << " <- " << inst.getOperand(0)
                        // << '\n';
                    }
                    constrainNominalType(&inst);
                    break;
                }
                case Instruction::BitCast: {
                    if (inst.getType()->isPointerTy() &&
                        inst.getOperand(0)->getType()->isPointerTy()) {
                        auto dstType = inst.getType()->getPointerElementType();
                        auto srcType = inst.getOperand(0)->getType()->getPointerElementType();
                        if (dstType->isStructTy()) {
                            constrainNominalType(&inst);
                            if (srcType->isStructTy()) {
                                constraintSystem.addConstraint(&inst, inst.getOperand(0));
                            }
                        }
                    }
                    break;
                }
                case Instruction::Call:
                case Instruction::Invoke: {
                    handleCallBase(dyn_cast<CallBase>(&inst));
                    constrainNominalType(&inst);
                    break;
                }
                default: {
                    // outs() << "Unknown opcode " << inst.getOpcodeName() << '\n';
                }
            }
        }
    }

    constraintSystem.buildGraph();
}

set<string> FunctionObjectFlow::traverseBack(const Value *val) {
    ConstraintSolverV2 solver(&constraintSystem);
    solver.solve();
    if (!solver.sanityCheck()) {
        string err = "Sanity check broken in function " + demangle(function->getName().str());
        throw std::runtime_error(err.c_str());
    }
    return solver.query(val);
}
