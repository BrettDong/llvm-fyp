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
#ifndef ANALYZER_H
#define ANALYZER_H

#include <llvm/Support/SourceMgr.h>

#include "ClassAnalyzer.h"
#include "Common.hpp"

class Analyzer {
   private:
    std::unique_ptr<llvm::LLVMContext> llvmContext;
    llvm::SMDiagnostic err;

    std::map<std::string, std::unique_ptr<llvm::Module>> modules;
    std::map<std::string, const llvm::Function *> functions;
    std::set<std::string> analyzedFunctions;

    std::map<std::string, ClassSet> functionRetTypes;

    std::unique_ptr<Symbols> symbols;
    std::unique_ptr<ClassAnalyzer> classes;

    int totalCHATargets = 0;
    int totalOFATargets = 0;
    int totalTrivialCallSites = 0;
    int totalNonTrivialCallSites = 0;

   private:
    std::optional<int> getVTableIndex(const llvm::CallBase *callInst) const;
    std::optional<HashTy> getVirtCallType(const llvm::CallBase *callInst) const;
    [[nodiscard]] std::set<std::string> collectVirtualMethods(const std::set<HashTy> &types,
                                                              int index) const;
    void analyzeVirtCall(const llvm::CallBase *callInst);
    void analyzeFunction(const llvm::Function &f);

   public:
    Analyzer();

    void analyze(const std::vector<std::string> &files);
};

#endif