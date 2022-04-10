#include "FunctionObjectFlow.h"

#include <queue>

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

    for (size_t i = 0; i < f->arg_size(); i++) {
        const Argument *arg = f->getArg(i);
        arguments.emplace_back(arg);
        if (arg->getType()->isPointerTy()) {
            // argumentTypes.insert({i, arg->getType()->getPointerElementType()});
        }
    }

    for (auto &bb : *f) {
        for (auto &inst : bb) {
            switch (inst.getOpcode()) {
                case Instruction::Alloca: {
                    alloca.insert(&inst);
                    // outs() << "ALLOCA " << &inst << '\n';
                    break;
                }
                case Instruction::Load: {
                    if (inst.getType()->isPointerTy()) {
                        solver.addConstraint(inst.getOperand(0), &inst);
                        // addEdge(inst.getOperand(0), &inst, ConstraintType::Widen);
                        // outs() << "LOAD " << &inst << " <- " << inst.getOperand(0) << '\n';
                    }
                    break;
                }
                case Instruction::Store: {
                    if (inst.getOperand(0)->getType()->isPointerTy()) {
                        solver.addConstraint(inst.getOperand(0), inst.getOperand(1));
                        // addEdge(inst.getOperand(0), inst.getOperand(1), ConstraintType::Widen);
                        // outs() << "STORE " << inst.getOperand(1) << " <- " << inst.getOperand(0)
                        // << '\n';
                    }
                    break;
                }
                case Instruction::BitCast: {
                    if (inst.getType()->isPointerTy() &&
                        inst.getOperand(0)->getType()->isPointerTy()) {
                        auto dstType = inst.getType()->getPointerElementType();
                        auto srcType = inst.getOperand(0)->getType()->getPointerElementType();
                        if (dstType->isStructTy()) {
                            string className = stripClassName(dstType->getStructName().str());
                            solver.addLiteralConstraint(
                                &inst, classes->getHierarchyGraph().querySelfWithDerivedClasses(
                                           className));
                            if (srcType->isStructTy()) {
                                solver.addConstraint(&inst, inst.getOperand(0));
                            }
                        }
                    }
                    break;
                }
                case Instruction::Call:
                case Instruction::Invoke: {
                    handleCallBase(dyn_cast<CallBase>(&inst));
                    break;
                }
                default: {
                    // outs() << "Unknown opcode " << inst.getOpcodeName() << '\n';
                }
            }
        }
    }
}

set<string> FunctionObjectFlow::traverseBack(const Value *val) {
    solver.buildGraph();
    solver.solve();
    return solver.query(val);
}
