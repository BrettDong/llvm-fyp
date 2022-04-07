#pragma once
#ifndef FUNCTION_OBJECT_FLOW_H
#define FUNCTION_OBJECT_FLOW_H

#include "Common.hpp"

class FunctionObjectFlow {
   private:
    vector<const Value *> arguments;
    set<const Value *> alloca;
    set<const Value *> retVals;
    map<const Value *, set<string>> instantiations;
    map<const Value *, set<const Value *>> edges;
    const Function *function;

    void addEdge(const Value *src, const Value *dst);

    void addInstantiation(const Value *dst, const string &className);

    void handleCallBase(const Instruction *inst);

   public:
    void analyzeFunction(const Function *f);

    void traverseBack(const Value *val);
};

#endif  // FUNCTION_OBJECT_FLOW_H