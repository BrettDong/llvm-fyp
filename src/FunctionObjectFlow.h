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