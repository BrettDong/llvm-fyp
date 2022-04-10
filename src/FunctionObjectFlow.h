#pragma once
#ifndef FUNCTION_OBJECT_FLOW_H
#define FUNCTION_OBJECT_FLOW_H

#include "ClassAnalyzer.h"
#include "Common.hpp"
#include "ConstraintSystem.h"

class FunctionObjectFlow {
   private:
    vector<const Value *> arguments;
    set<const Value *> alloca;
    set<const Value *> retVals;
    map<const Value *, set<string>> instantiations;

    ConstraintSystem constraintSystem;

    ClassAnalyzer *classes;
    const Function *function;

    void addInstantiation(const Value *dst, const string &className);

    void handleCallBase(const Instruction *inst);

   public:
    explicit FunctionObjectFlow(ClassAnalyzer *classes) : classes(classes), function(nullptr) {}

    void analyzeFunction(const Function *f);

    set<string> traverseBack(const Value *val);
};

#endif  // FUNCTION_OBJECT_FLOW_H