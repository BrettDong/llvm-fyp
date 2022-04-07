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

   private:
    std::optional<int> getVTableIndex(const CallInst *callInst) const;
    std::optional<string> getVirtCallType(const CallInst *callInst) const;
    void analyzeVirtCall(const CallInst *callInst);
    void analyzeFunction(const Function &f);

   public:
    Analyzer();

    void analyze(const vector<string>& files);
};

#endif