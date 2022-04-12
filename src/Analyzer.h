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

    std::map<std::string, std::set<std::string>> functionRetTypes;

    ClassAnalyzer classes;

    int totalCHATargets = 0;
    int totalOFATargets = 0;
    int totalTrivialCallSites = 0;
    int totalNonTrivialCallSites = 0;

   private:
    std::optional<int> getVTableIndex(const llvm::CallBase *callInst) const;
    std::optional<std::string> getVirtCallType(const llvm::CallBase *callInst) const;
    [[nodiscard]] std::set<std::string> collectVirtualMethods(const std::set<std::string> &types,
                                                              int index) const;
    void analyzeVirtCall(const llvm::CallBase *callInst);
    void analyzeFunction(const llvm::Function &f);

   public:
    Analyzer();

    void analyze(const std::vector<std::string> &files);
};

#endif