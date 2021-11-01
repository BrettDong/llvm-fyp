#pragma once
#ifndef CALL_GRAPH_H
#define CALL_GRAPH_H

#include <llvm/Analysis/AliasAnalysis.h>

#define MLTA_FOR_INDIRECT_CALL 1

//extern cl::opt<unsigned> VerboseLevel;
extern map<Type *, string> TypeToTNameMap;
extern const DataLayout *CurrentLayout;

#define LOG(lv, stmt)                           \
    do {                                        \
        if (VerboseLevel >= lv) errs() << stmt; \
    } while (0)

#define OP llvm::outs()

//
// typedefs
//
typedef vector<pair<llvm::Module *, llvm::StringRef>> ModuleList;
// Mapping module to its file name.
typedef unordered_map<llvm::Module *, llvm::StringRef> ModuleNameMap;
// The set of all functions.
typedef llvm::SmallPtrSet<llvm::Function *, 8> FuncSet;
// Mapping from function name to function.
typedef unordered_map<string, llvm::Function *> NameFuncMap;
typedef llvm::SmallPtrSet<llvm::CallInst *, 8> CallInstSet;
typedef DenseMap<Function *, CallInstSet> CallerMap;
typedef DenseMap<CallInst *, FuncSet> CalleeMap;
// Pointer analysis types.
typedef DenseMap<Value *, SmallPtrSet<Value *, 16>> PointerAnalysisMap;
typedef unordered_map<Function *, PointerAnalysisMap> FuncPointerAnalysisMap;
typedef unordered_map<Function *, AAResults *> FuncAAResultsMap;
typedef map<Type *, string> TypeNameMap;


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
    GlobalContext() {
        // Initialize statistucs.
        NumSecurityChecks = 0;
        NumCondStatements = 0;
    }

    unsigned NumSecurityChecks;
    unsigned NumCondStatements;

    // Map global types to type_name
    TypeNameMap GlobalTypes;

    // Map global function name to function.
    NameFuncMap GlobalFuncs;

    // Functions whose addresses are taken.
    FuncSet AddressTakenFuncs;

    // Map a callsite to all potential callee functions.
    CalleeMap Callees;

    // Map a function to all potential caller instructions.
    CallerMap Callers;

    // Indirect call instructions.
    std::vector<CallInst *> IndirectCallInsts;

    // Unified functions -- no redundant inline functions
    DenseMap<size_t, Function *> UnifiedFuncMap;
    set<Function *> UnifiedFuncSet;

    // Map function signature to functions
    DenseMap<size_t, FuncSet> sigFuncsMap;

    // Modules.
    ModuleList Modules;
    ModuleNameMap ModuleMaps;
    set<string> InvolvedModules;

    // SecurityChecksPass
    // Functions handling errors
    set<string> ErrorHandleFuncs;
    map<string, tuple<int8_t, int8_t, int8_t>> CopyFuncs;

    // Identified sanity checks
    DenseMap<Function *, set<SecurityCheck>> SecurityCheckSets;
    DenseMap<Function *, set<Value * >> CheckInstSets;

    // Pointer analysis results.
    FuncPointerAnalysisMap FuncPAResults;
    FuncAAResultsMap FuncAAResults;

    map<string, pair<int8_t, int8_t>> DataFetchFuncs;
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

class CallGraphPass : public IterativeModulePass {
private:
    const DataLayout *DL;
    // char * or void *
    Type *Int8PtrTy;
    // long interger type
    Type *IntPtrTy;

    static DenseMap<size_t, FuncSet> typeFuncsMap;
    static unordered_map<size_t, set<size_t>> typeConfineMap;
    static unordered_map<size_t, set<size_t>> typeTransitMap;
    static set<size_t> typeEscapeSet;

    // Use type-based analysis to find targets of indirect calls
    void findCalleesWithType(llvm::CallInst *, FuncSet &);

    void unrollLoops(Function *F);

    bool isCompositeType(Type *Ty);
    bool typeConfineInInitializer(User *Ini);
    bool typeConfineInStore(StoreInst *SI);
    bool typeConfineInCast(CastInst *CastI);
    void escapeType(Type *Ty, int Idx = -1);
    void transitType(Type *ToTy, Type *FromTy, int ToIdx = -1, int FromIdx = -1);

    Value *nextLayerBaseType(Value *V, Type *&BTy, int &Idx, const DataLayout *_DL);

    void funcSetIntersection(FuncSet &FS1, FuncSet &FS2, FuncSet &FS);
    bool findCalleesWithMLTA(CallInst *CI, FuncSet &FS);

public:
    CallGraphPass(GlobalContext *Ctx_) : IterativeModulePass(Ctx_, "CallGraph") {}

    virtual bool doInitialization(llvm::Module *);
    virtual bool doFinalization(llvm::Module *);
    virtual bool doModulePass(llvm::Module *);
};

#endif
