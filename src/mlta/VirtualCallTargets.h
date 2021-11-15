#pragma once

#include "llvm/IR/Dominators.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/IPO/WholeProgramDevirt.h"

namespace virtcall {

using FunctionSet = llvm::SmallPtrSet<llvm::Function *, 8>;

////////////////////////////////////////////////////////////////////////////////

class VirtualCallTargetsResult {
   public:
    void addVirtualCallCandidates(llvm::CallInst *call, FunctionSet &&candidates);
    void addVirtualInvokeCandidates(llvm::InvokeInst *call, FunctionSet &&candidates);
    bool hasVirtualCallCandidates(llvm::Instruction *instr) const;
    const FunctionSet &getVirtualCallCandidates(llvm::Instruction *instr) const;
    void dump();

   private:
    void addCandidates(llvm::Instruction *instr, FunctionSet &&candidates);
    std::unordered_map<llvm::Instruction *, FunctionSet> m_virtualCallCandidates;
    FunctionSet m_emptyFunctionSet;
};  // class VirtualCallTargetsResult

////////////////////////////////////////////////////////////////////////////////

class VirtualCallResolver {
   public:
    static void ResolveVirtualCalls(llvm::Module &M, VirtualCallTargetsResult &result);
};

////////////////////////////////////////////////////////////////////////////////

}  // end namespace virtcall
