#pragma once

#include "Common.h"

enum AnalysisType { mlta_pref, mlta_only, ta_only };
enum Demangle { demangle_debug_only, demangle_all, demangle_none };

//
// typedefs
//
typedef vector<pair<llvm::Module *, std::string>> ModuleList;
// The set of all functions.
typedef llvm::SmallPtrSet<llvm::Function *, 8> FuncSet;
// Mapping from function name to function.
typedef unordered_map<string, llvm::Function *> NameFuncMap;

class SecurityCheck {
   public:
    SecurityCheck(Value *sk, Value *br) : SCheck(sk), SCBranch(br) {
        auto I = dyn_cast<Instruction>(SCheck);
        if (!I) return;

        MDNode *N = I->getMetadata("dbg");
        if (!N) return;

        DILocation *Loc = dyn_cast<DILocation>(N);
        if (!Loc || Loc->getLine() < 1) return;

        SCheckFileName = Loc->getFilename().str();
        SCheckLineNo = Loc->getLine();
    }

    ~SecurityCheck() {}

    Value *getSCheck() { return SCheck; }

    Value *getSCBranch() { return SCBranch; }

    string getSCheckFileName() { return SCheckFileName; }

    unsigned getSCheckLineNo() { return SCheckLineNo; }

    friend bool operator<(const SecurityCheck &SC1, const SecurityCheck &SC2) {
        return (SC1.SCheck < SC2.SCheck);
    }

   private:
    Value *SCheck;         /* Security check of this critical variable */
    Value *SCBranch;       /* Branch associated to the check */
    string SCheckFileName; /* Source file name of security check */
    unsigned SCheckLineNo; /* Line number of security check */
};

struct GlobalContext {
    GlobalContext() {}

    // Map global function name to function.
    NameFuncMap GlobalFuncs;

    // Functions whose addresses are taken.
    FuncSet AddressTakenFuncs;

    // Unified functions -- no redundant inline functions
    DenseMap<size_t, Function *> UnifiedFuncMap;

    // Map function signature to functions
    DenseMap<size_t, FuncSet> sigFuncsMap;

    // Modules.
    ModuleList Modules;

    // Command line arguments
    AnalysisType analysisType = mlta_pref;
    Demangle demangle = demangle_all;
    ofstream csvout;
};

class IterativeModulePass {
   protected:
    GlobalContext *Ctx;
    const char *ID;

   public:
    IterativeModulePass(GlobalContext *Ctx_, const char *ID_) : Ctx(Ctx_), ID(ID_) {}

    // Run on each module before iterative pass.
    virtual bool doInitialization(llvm::Module *M) { return true; }

    // Run on each module after iterative pass.
    virtual bool doFinalization(llvm::Module *M) { return true; }

    // Iterative pass.
    virtual bool doModulePass(llvm::Module *M) { return false; }

    virtual void run(ModuleList &modules);
};
