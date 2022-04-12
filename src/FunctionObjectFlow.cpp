#include "FunctionObjectFlow.h"

#include <queue>

#include "ConstraintSolver.h"
#include "Utils.h"

using namespace std;
using namespace llvm;

void FunctionObjectFlow::handleCallBase(const Instruction *inst) {
    if (classes->isPolymorphicType(inst->getType())) {
        auto callInst = dyn_cast<CallBase>(inst);
        auto callee = callInst->getCalledFunction();
        if (callee != nullptr && functionRetTypes.count(callee->getName().str()) > 0) {
            constraintSystem.addLiteralConstraint(dyn_cast<Value>(inst),
                                                  functionRetTypes[callee->getName().str()],
                                                  ConstraintRelation::Superset);
        } else {
            auto nominalTy = inst->getType()->getPointerElementType()->getStructName();
            constraintSystem.addLiteralConstraint(
                dyn_cast<Value>(inst),
                classes->getSelfAndDerivedClasses(symbols->hashClassName(nominalTy)),
                ConstraintRelation::Superset);
        }
    }
}

void FunctionObjectFlow::analyzeFunction(const Function *f) {
    function = f;

    auto constrainNominalType = [=](const Value *v) {
        if (classes->isPolymorphicType(v->getType())) {
            auto className = v->getType()->getPointerElementType()->getStructName();
            auto hash = symbols->hashClassName(className);
            constraintSystem.addLiteralConstraint(v, classes->getSelfAndDerivedClasses(hash));
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
                case Instruction::Ret: {
                    if (inst.getNumOperands() > 0) {
                        const Value *operand = inst.getOperand(0);
                        if (classes->isPolymorphicType(operand->getType())) {
                            constrainNominalType(operand);
                            ret.emplace_back(operand);
                        }
                    }
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

set<HashTy> FunctionObjectFlow::traverseBack(const Value *val) {
    ConstraintSolverV2 solver(&constraintSystem);
    solver.solve();
    if (!solver.sanityCheck()) {
        string err = "Sanity check broken in function " + demangle(function->getName().str());
        throw std::runtime_error(err.c_str());
    }
    return solver.query(val);
}

set<HashTy> FunctionObjectFlow::queryRetType() {
    ConstraintSolverV2 solver(&constraintSystem);
    solver.solve();
    if (!solver.sanityCheck()) {
        string err = "Sanity check broken in function " + demangle(function->getName().str());
        throw std::runtime_error(err.c_str());
    }
    set<HashTy> ans;
    for (const Value *r : ret) {
        for (const HashTy &target : solver.query(r)) {
            ans.insert(target);
        }
    }
    return ans;
}
