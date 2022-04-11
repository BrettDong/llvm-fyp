#pragma once
#ifndef FUNCTION_OBJECT_FLOW_H
#define FUNCTION_OBJECT_FLOW_H

#include "ClassAnalyzer.h"
#include "Common.hpp"
#include "ConstraintSystem.h"

class FunctionObjectFlow {
   private:
    vector<const Value *> arguments;

    ConstraintSystem constraintSystem;

    ClassAnalyzer *classes;
    const Function *function = nullptr;
    vector<const Value *> ret;

    void handleCallBase(const Instruction *inst);

   public:
    explicit FunctionObjectFlow(ClassAnalyzer *classes) : classes(classes) {}

    void analyzeFunction(const Function *f);

    set<string> traverseBack(const Value *val);

    set<string> queryRetType();
};

#endif  // FUNCTION_OBJECT_FLOW_H