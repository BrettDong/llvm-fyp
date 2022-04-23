// Copyright 2022 Binrui Dong
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Analyzer.h"

#include <llvm/IRReader/IRReader.h>

#include "ClassSet.h"
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

std::optional<ClassSymbol> Analyzer::getVirtCallType(const CallBase *callInst) const {
    auto getClassType = [this](const Value *operand) -> std::optional<ClassSymbol> {
        if (classes->isPolymorphicType(operand->getType())) {
            auto className = operand->getType()->getPointerElementType()->getStructName();
            return symbols->hashClassName(className);
        }
        return std::nullopt;
    };

    if (callInst->hasStructRetAttr()) {
        if (callInst->arg_size() < 2) {
            return std::nullopt;
        }
        return getClassType(callInst->getArgOperand(1));
    } else {
        if (callInst->arg_size() < 1) {
            return std::nullopt;
        }
        return getClassType(callInst->getArgOperand(0));
    }
}

set<string> Analyzer::collectVirtualMethods(const set<ClassSymbol> &types, int index) const {
    set<string> targets;
    for (const ClassSymbol className : types) {
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
    set<ClassSymbol> derivedClasses = classes->getSelfAndDerivedClasses(type.value()).toClasses();

    set<string> CHA = collectVirtualMethods(derivedClasses, index.value());

    const Value *obj = callInst->getOperand(0);
    FunctionObjectFlow flow(classes.get(), symbols.get(), functionRetTypes);
    flow.analyzeFunction(callInst->getParent()->getParent());
    set<string> OFA = collectVirtualMethods(flow.traverseBack(obj).toClasses(), index.value());
    if (OFA.empty()) OFA = CHA;

    if (CHA.empty()) {
        outs() << "No target found when calling \"" << symbols->getClassName(type.value())
               << "\" at vtable index " << index.value() << " in "
               << (callInst->getFunction()->getName().str()) << " : " << *callInst << '\n';
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
    symbols = std::make_unique<ClassSymbolManager<ClassSymbol>>();
    classes = std::make_unique<ClassAnalyzer>(symbols.get());
}

static void printTime(const decltype(chrono::system_clock::now()) &start) {
    float seconds = chrono::duration<float>(chrono::system_clock::now() - start).count();
    ostringstream oss;
    oss.precision(3);
    oss << fixed << seconds;
    outs() << "[" << oss.str() << "] ";
}

void Analyzer::analyze(vector<string> files) {
    bool keepIR = files.size() < 1000;

    auto for_each_module = [&](const std::function<void(const std::string &, llvm::Module *)> &f) {
        if (keepIR) {
            for (const auto &[file, module] : modules) {
                f(file, module.get());
            }
        } else {
            for (auto it = files.begin(); it != files.end();) {
                const auto &file = *it;
                unique_ptr<Module> module = parseIRFile(file, err, *llvmContext);
                if (!module) {
                    errs() << "Error loading \"" << file << "\": " << err.getMessage() << "\n";
                    it = files.erase(it);
                } else {
                    f(file, module.get());
                    ++it;
                }
            }
        }
    };

    auto start = chrono::system_clock::now();
    if (keepIR) {
        printTime(start);
        outs() << "Parsing LLVM IR from " << files.size() << " modules" << '\n';
        for (auto it = files.begin(); it != files.end();) {
            const auto &file = *it;
            unique_ptr<Module> module = parseIRFile(file, err, *llvmContext);
            if (!module) {
                errs() << "Error loading bitcode file \"" << file << "\": " << err.getMessage()
                       << "\n";
                it = files.erase(it);
            } else {
                modules[file] = std::move(module);
                ++it;
            }
        }
    }

    printTime(start);
    outs() << "Decoding virtual tables and RTTI" << '\n';
    for_each_module(
        [&](const std::string &file, llvm::Module *module) { classes->analyzeModule(module); });

    printTime(start);
    outs() << "Clustering " << classes->getAllClasses().size() << " classes" << '\n';
    classes->clusterClasses();

    printTime(start);
    outs() << "Building class hierarchy graph in " << classes->clusterCount() << " clusters"
           << '\n';
    classes->buildClassHierarchyGraph();

    printTime(start);
    outs() << "Analyzing function return types" << '\n';
    for_each_module([&](const std::string &file, llvm::Module *module) {
        for (const Function &f : *module) {
            if (f.getInstructionCount() == 0) continue;
            if (analyzedFunctions.count(f.getName().str()) > 0) continue;
            analyzedFunctions.insert(f.getName().str());
            Type *retType = nullptr;
            if (f.getReturnType()->isVoidTy()) {
                if (f.arg_size() > 1 && f.getArg(0)->getType()->isStructTy()) {
                    retType = f.getArg(0)->getType();
                }
            } else if (f.getReturnType()->isPointerTy() &&
                       f.getReturnType()->getPointerElementType()->isStructTy()) {
                retType = f.getReturnType();
            }
            if (retType && classes->isPolymorphicType(retType)) {
                FunctionObjectFlow flow(classes.get(), symbols.get(), functionRetTypes);
                flow.analyzeFunction(&f);
                ClassSet OFA = flow.queryRetType();
                auto className = retType->getPointerElementType()->getStructName();
                auto hash = symbols->hashClassName(className);
                ClassSet CHA = classes->getSelfAndDerivedClasses(hash);
                if (!OFA.empty() && OFA.count() < CHA.count()) {
                    functionRetTypes.insert({f.getName().str(), OFA});
                }
            }
        }
    });

    printTime(start);
    outs() << "Analyzing virtual calls in " << analyzedFunctions.size() << " functions" << '\n';
    analyzedFunctions.clear();

    for_each_module([&](const std::string &file, llvm::Module *module) {
        for (const Function &f : *module) {
            if (f.getInstructionCount() == 0) continue;
            if (analyzedFunctions.count(f.getName().str()) > 0) continue;
            analyzedFunctions.insert(f.getName().str());
            analyzeFunction(f);
        }
    });

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
