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

#pragma once
#ifndef FUNCTION_OBJECT_FLOW_H
#define FUNCTION_OBJECT_FLOW_H

#include "ClassAnalyzer.h"
#include "Common.hpp"
#include "ConstraintSystem.h"

class FunctionObjectFlow {
   private:
    std::vector<const llvm::Value *> arguments;

    ConstraintSystem constraintSystem;

    ClassAnalyzer *classes;
    Symbols *symbols;
    std::map<std::string, std::set<HashTy>> &functionRetTypes;
    const llvm::Function *function = nullptr;
    std::vector<const llvm::Value *> ret;

    void handleCallBase(const llvm::Instruction *inst);

   public:
    explicit FunctionObjectFlow(ClassAnalyzer *classes, Symbols *symbols,
                                std::map<std::string, std::set<HashTy>> &functionRetTypes)
        : classes(classes), symbols(symbols), functionRetTypes(functionRetTypes) {}

    void analyzeFunction(const llvm::Function *f);

    std::set<HashTy> traverseBack(const llvm::Value *val);

    std::set<HashTy> queryRetType();
};

#endif  // FUNCTION_OBJECT_FLOW_H