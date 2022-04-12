#include "Analyzer.h"

#include <llvm/IRReader/IRReader.h>

#include "FunctionObjectFlow.h"
#include "Utils.h"

using namespace std;
using namespace llvm;

std::optional<int> Analyzer::getVTableIndex(const CallBase *callInst) const {
    const LoadInst *loadInst = dyn_cast<LoadInst>(callInst->getCalledOperand());
    if (loadInst == nullptr) return std::nullopt;

    const auto *GEP = dyn_cast<GetElementPtrInst>(loadInst->getPointerOperand());
    if (GEP == nullptr) return std::nullopt;

    const ConstantInt *index = dyn_cast<ConstantInt>(GEP->getOperand(1));
    if (index == nullptr) return std::nullopt;

    return index->getZExtValue();
}

std::optional<HashTy> Analyzer::getVirtCallType(const CallBase *callInst) const {
    if (callInst->arg_size() < 1) return std::nullopt;
    if (const Type *type = callInst->getArgOperand(0)->getType()) {
        if (type->isPointerTy() && type->getPointerElementType()->isStructTy()) {
            auto name = type->getPointerElementType()->getStructName();
            if (classes->isPolymorphicType(name)) {
                return symbols->hashClassName(name);
            }
        }
    }
    return std::nullopt;
}

set<string> Analyzer::collectVirtualMethods(const set<HashTy> &types, int index) const {
    set<string> targets;
    for (const HashTy className : types) {
        auto vTable = classes->getClass(className).getVTable();
        if (vTable.empty()) {
            // outs() << derived << " does not have VTable!\n";
            continue;
        }
        if (index >= vTable.size()) {
            continue;
        }
        const std::string &target = vTable[index];
        if (target.empty()) {
            // outs() << index.value() << " is out-of-bound in VTable of " << derived << '\n';
            continue;
        }
        targets.insert(demangle(target));
    }
    auto pure_virtual = targets.find("__cxa_pure_virtual");
    if (pure_virtual != targets.end()) {
        targets.erase(pure_virtual);
    }
    return targets;
}

void Analyzer::analyzeVirtCall(const CallBase *callInst) {
    auto index = getVTableIndex(callInst);
    if (!index.has_value()) {
        // outs() << "cannot get vtable index" << '\n';
        return;
    }
    auto type = getVirtCallType(callInst);
    if (!type.has_value()) {
        // outs() << "cannot get virt call type" << '\n';
        return;
    }
    set<HashTy> derivedClasses = classes->getSelfAndDerivedClasses(type.value());

    set<string> CHA = collectVirtualMethods(derivedClasses, index.value());

    const Value *obj = callInst->getOperand(0);
    FunctionObjectFlow flow(classes.get(), symbols.get(), functionRetTypes);
    flow.analyzeFunction(callInst->getParent()->getParent());
    set<string> OFA = collectVirtualMethods(flow.traverseBack(obj), index.value());
    if (OFA.empty()) OFA = CHA;

    if (CHA.empty()) {
        outs() << "No target found when calling \"" << type.value() << "\" at vtable index "
               << index.value() << " in " << (callInst->getFunction()->getName().str()) << " : "
               << *callInst << '\n';
    } else if (CHA.size() == 1) {
        ++totalTrivialCallSites;
    } else {
        ++totalNonTrivialCallSites;
        totalCHATargets += CHA.size();
        totalOFATargets += OFA.size();
    }
    if (CHA == OFA) {
        return;
    }
    outs() << "In function " << demangle(callInst->getFunction()->getName().str()) << "\n";
    outs() << "At virtual call " << *callInst << "\n";
    outs() << "Class hierarchy analysis (" << CHA.size() << "): " << list_out(CHA) << '\n';
    outs() << "Object-flow analysis (" << OFA.size() << "): " << list_out(OFA) << '\n';
    outs() << '\n';
}

void Analyzer::analyzeFunction(const Function &f) {
    for (auto &bb : f) {
        for (auto &inst : bb) {
            if (auto callInst = dyn_cast<CallBase>(&inst)) {
                if (callInst->getCalledFunction() == nullptr) {
                    analyzeVirtCall(callInst);
                }
            }
        }
    }
}

Analyzer::Analyzer() {
    llvmContext = make_unique<LLVMContext>();
    symbols = std::make_unique<Symbols>();
    classes = std::make_unique<ClassAnalyzer>(symbols.get());
}

static void printTime(const decltype(chrono::system_clock::now()) &start) {
    float seconds = chrono::duration<float>(chrono::system_clock::now() - start).count();
    ostringstream oss;
    oss.precision(3);
    oss << fixed << seconds;
    outs() << "[" << oss.str() << "] ";
}

void Analyzer::analyze(const vector<string> &files) {
    auto start = chrono::system_clock::now();
    printTime(start);
    outs() << "Parsing LLVM IR from " << files.size() << " modules" << '\n';
    for (const string &file : files) {
        // outs() << "Reading bitcode file: " << file << "\n";
        unique_ptr<Module> module = parseIRFile(file, err, *llvmContext);
        if (!module) {
            errs() << "Error loading bitcode file \"" << file << "\": " << err.getMessage() << "\n";
            continue;
        }
        modules[file] = std::move(module);
    }

    printTime(start);
    outs() << "Analyzing class inheritance relationships" << '\n';
    for (const auto &[file, module] : modules) {
        // outs() << "Decoding class information from " << file << '\n';
        classes->analyzeModule(module.get());
    }

    printTime(start);
    outs() << "Building class hierarchy graph" << '\n';
    classes->buildClassHierarchyGraph();

    for (const auto &[file, module] : modules) {
        // outs() << "Decoding functions from " << file << '\n';
        for (const Function &f : *module) {
            if (f.getInstructionCount() == 0) continue;
            functions[f.getName().str()] = &f;
        }
    }

    for (const auto &[name, f] : functions) {
        if (classes->isPolymorphicType(f->getReturnType())) {
            FunctionObjectFlow flow(classes.get(), symbols.get(), functionRetTypes);
            flow.analyzeFunction(f);
            set<HashTy> OFA = flow.queryRetType();
            auto className = f->getReturnType()->getPointerElementType()->getStructName();
            auto hash = symbols->hashClassName(className);
            set<HashTy> CHA = classes->getSelfAndDerivedClasses(hash);
            if (!OFA.empty() && OFA.size() < CHA.size()) {
                functionRetTypes.insert({name, OFA});
            }
        }
    }

    printTime(start);
    outs() << "Analyzing " << functions.size() << " functions" << '\n';

    for (const auto &it : functions) {
        analyzeFunction(*it.second);
    }

    printTime(start);
    outs() << "Analysis completed" << '\n';
    outs() << "Total virtual call sites: " << totalTrivialCallSites + totalNonTrivialCallSites
           << '\n';
    outs() << "Total non-trivial virtual call sites: " << totalNonTrivialCallSites << '\n';
    outs() << "Total targets of non-trivial call sites reported by class hierarchy analysis: "
           << totalCHATargets << '\n';
    outs() << "Total targets of non-trivial call sites reported by object flow analysis: "
           << totalOFATargets << '\n';
}
