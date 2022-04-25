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

#include "ClassHierarchy.h"
#include "Common.hpp"

class Analyzer {
   private:
    std::unique_ptr<llvm::LLVMContext> llvmContext;
    llvm::SMDiagnostic err;

    std::map<std::string, std::unique_ptr<llvm::Module>> modules;
    std::map<std::string, const llvm::Function *> functions;
    std::set<std::string> analyzedFunctions;

    std::map<std::string, ClassSet> functionRetTypes;

    std::unordered_map<ClassSymbol, std::vector<FunctionSymbol>> vTables;

    std::unique_ptr<ClassSymbolManager<ClassSymbol>> classSymbols;
    std::unique_ptr<FunctionSymbolManager<FunctionSymbol>> functionSymbols;
    std::unique_ptr<ClassHierarchy> hierarchy;

    int totalCHATargets = 0;
    int totalOFATargets = 0;
    int totalTrivialCallSites = 0;
    int totalNonTrivialCallSites = 0;

   private:
    std::optional<int> getVTableIndex(const llvm::CallBase *callInst) const;
    std::optional<ClassSymbol> getVirtCallType(const llvm::CallBase *callInst) const;
    [[nodiscard]] std::set<FunctionSymbol> collectVirtualMethods(const std::set<ClassSymbol> &types,
                                                                 int index) const;
    void decodeVTable(ClassSymbol hash, const llvm::Constant *initializer);
    void decodeRTTI(ClassSymbol derived, const llvm::Constant *initializer);
    void analyzeVirtCall(const llvm::CallBase *callInst);
    void analyzeFunction(const llvm::Function &f);
    void analyzeGlobalVariable(const llvm::GlobalVariable *gv);

   public:
    Analyzer();

    void analyze(std::vector<std::string> files);
};

#endif