// Copyright 2022 Binrui Dong
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "FunctionObjectFlow.h"

#include <queue>

#include "ConstraintSolver.h"
#include "Utils.h"

using namespace std;
using namespace llvm;

void FunctionObjectFlow::handleCallBase(const Instruction *inst) {
    auto callInst = dyn_cast<CallBase>(inst);
    auto callee = callInst->getCalledFunction();
    if (callee == nullptr) {
        return;
    }
    if (functionRetTypes.count(callee->getName().str()) > 0) {
        constraintSystem.addLiteralConstraint(dyn_cast<Value>(inst),
                                              functionRetTypes.at(callee->getName().str()),
                                              ConstraintRelation::Superset);
    } else {
        Type *nominalTy = nullptr;
        if (callInst->getType()->isVoidTy()) {
            if (callInst->hasStructRetAttr() && callInst->arg_size() > 1) {
                nominalTy = callInst->getArgOperand(0)->getType();
            }
        } else if (callInst->getType()->isPointerTy() &&
                   callInst->getType()->getPointerElementType()->isStructTy()) {
            nominalTy = callInst->getType();
        }
        if (nominalTy && classes->isPolymorphicType(nominalTy)) {
            auto hash = symbols->hashClassName(nominalTy->getPointerElementType()->getStructName());
            constraintSystem.addLiteralConstraint(dyn_cast<Value>(inst),
                                                  classes->getSelfAndDerivedClasses(hash),
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

    if (f->hasStructRetAttr() && f->arg_size() > 1 &&
        classes->isPolymorphicType(f->getArg(0)->getType())) {
        ret.emplace_back(f->getArg(0));
    }

    for (auto &bb : *f) {
        for (auto &inst : bb) {
            // outs() << "Processing " << inst << '\n';
            switch (inst.getOpcode()) {
                case Instruction::Alloca: {
                    if (inst.getType()->isPointerTy()) {
                        auto elemTy = inst.getType()->getPointerElementType();
                        if (elemTy->isStructTy()) {
                            auto className = elemTy->getStructName();
                            if (classes->isPolymorphicType(className)) {
                                auto hash = symbols->hashClassName(className);
                                auto classSet = classes->getSelfAndDerivedClasses(hash);
                                constraintSystem.addLiteralConstraint(&inst, classSet);
                            }
                        }
                    } else if (inst.getType()->isStructTy()) {
                        auto className = inst.getType()->getStructName();
                        if (classes->isPolymorphicType(className)) {
                            auto hash = symbols->hashClassName(className);
                            auto classSet = classes->getSelfAndDerivedClasses(hash);
                            constraintSystem.addLiteralConstraint(&inst, classSet);
                        }
                    }
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

ClassSet FunctionObjectFlow::traverseBack(const Value *val) {
    ConstraintSolver solver(&constraintSystem, classes);
    solver.solve();
    return solver.query(val);
}

ClassSet FunctionObjectFlow::queryRetType() {
    ConstraintSolver solver(&constraintSystem, classes);
    solver.solve();
    ClassSet ans(classes);
    for (const Value *r : ret) {
        ans.unionWith(solver.query(r));
    }
    return ans;
}
