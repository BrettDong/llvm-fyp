#pragma once
#ifndef ANALYZER_H
#define ANALYZER_H

#include "ClassAnalyzer.h"
#include "Common.hpp"

class Analyzer {
   private:
    unique_ptr<LLVMContext> llvmContext;
    SMDiagnostic err;

    map<string, unique_ptr<Module>> modules;
    map<string, const Function *> functions;

    ClassAnalyzer classes;

    int totalCHATargets = 0;
    int totalOFATargets = 0;
    int totalCallSites = 0;

   private:
    std::optional<int> getVTableIndex(const CallBase *callInst) const;
    std::optional<string> getVirtCallType(const CallBase *callInst) const;
    [[nodiscard]] std::set<string> collectVirtualMethods(const set<string> &types, int index) const;
    void analyzeVirtCall(const CallBase *callInst);
    void analyzeFunction(const Function &f);

   public:
    Analyzer();

    void analyze(const vector<string> &files);
};

#endif