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

#include "ClassHierarchy.h"
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
        if (hierarchy->isPolymorphicPointerType(operand->getType())) {
            auto className = operand->getType()->getPointerElementType()->getStructName();
            return classSymbols->hashClassName(className);
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

set<FunctionSymbol> Analyzer::collectVirtualMethods(const set<ClassSymbol> &types,
                                                    int index) const {
    set<FunctionSymbol> targets;
    for (const ClassSymbol classSymbol : types) {
        if (vTables.count(classSymbol) == 0) {
            continue;
        }
        const auto &vTable = vTables.at(classSymbol);
        if (index >= vTable.size()) {
            continue;
        }
        if (vTable[index] != functionSymbols->hashFunctionName("__cxa_pure_virtual")) {
            targets.insert(vTable[index]);
        }
    }
    return targets;
}

void Analyzer::decodeVTable(ClassSymbol hash, const Constant *initializer) {
    if (vTables.count(hash) > 0) {
        return;
    }
    const auto *aggregate = dyn_cast<ConstantAggregate>(initializer);
    if (aggregate == nullptr) {
        return;
    }
    for (size_t i = 0; i < aggregate->getNumOperands(); i++) {
        if (const auto *array = dyn_cast<ConstantArray>(aggregate->getAggregateElement(i))) {
            for (size_t j = 0; j < array->getNumOperands(); j++) {
                if (auto *expr = dyn_cast<ConstantExpr>(array->getAggregateElement(j))) {
                    if (expr->isCast()) {
                        auto *constant = dyn_cast<Constant>(expr);
                        if (Constant *cast = ConstantExpr::getBitCast(constant, expr->getType())) {
                            Value *operand = cast->getOperand(0);
                            if (auto *f = dyn_cast<Function>(operand)) {
                                auto fnHash = functionSymbols->hashFunctionName(f->getName());
                                vTables[hash].push_back(fnHash);
                            } else if (auto *a = dyn_cast<GlobalAlias>(operand)) {
                                if (auto *af = dyn_cast<Function>(a->getAliasee())) {
                                    auto fnHash = functionSymbols->hashFunctionName(af->getName());
                                    vTables[hash].push_back(fnHash);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Analyzer::decodeRTTI(ClassSymbol derived, const Constant *initializer) {
    const auto *aggregate = dyn_cast<ConstantAggregate>(initializer);
    if (aggregate == nullptr) {
        return;
    }
    for (size_t i = 0; i < aggregate->getNumOperands(); i++) {
        if (auto *expr = dyn_cast<ConstantExpr>(aggregate->getAggregateElement(i))) {
            if (expr->isCast()) {
                auto *constant = dyn_cast<Constant>(expr);
                if (Constant *cast = ConstantExpr::getBitCast(constant, expr->getType())) {
                    if (auto *v = dyn_cast<GlobalVariable>(cast->getOperand(0))) {
                        std::string name = demangle(v->getName().str());
                        if (beginsWith(name, "typeinfo for ")) {
                            std::string baseName = removePrefix(name, "typeinfo for ");
                            auto base = classSymbols->hashClassName(baseName);
                            hierarchy->addRelation(base, derived);
                        }
                    }
                }
            }
        }
    }
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
    if (beginsWith(classSymbols->getClassName(type.value()), "std::")) {
        return;
    }
    ClassSet CHATypes = hierarchy->query(type.value());
    set<FunctionSymbol> CHA = collectVirtualMethods(CHATypes.toClasses(), index.value());
    if (CHA.empty()) {
        outs() << "Error: CHA finds no target when calling \""
               << classSymbols->getClassName(type.value()) << "\" at vtable index " << index.value()
               << " in " << (callInst->getFunction()->getName().str()) << " : " << *callInst
               << '\n';
        return;
    } else if (CHA.size() == 1) {
        ++totalTrivialCallSites;
        return;
    }

    const Value *obj = nullptr;
    if (callInst->hasStructRetAttr()) {
        obj = callInst->getOperand(1);
    } else {
        obj = callInst->getOperand(0);
    }
    FunctionObjectFlow flow(hierarchy.get(), classSymbols.get(), functionRetTypes);
    try {
        flow.analyzeFunction(callInst->getParent()->getParent());
        ClassSet OFATypes = flow.traverseBack(obj);

        set<FunctionSymbol> OFA;
        if (OFATypes.count() == 0) {
            outs() << "Error: OFA reports null set in "
                   << demangle(callInst->getFunction()->getName().str()) << " : " << *callInst
                   << '\n';
            outs() << "Class hierarchy analysis (" << CHA.size() << "): ";
            for (const auto fnHash : CHA) {
                outs() << "\"" << demangle(functionSymbols->getFunctionName(fnHash)) << "\" ";
            }
            outs() << '\n';
            outs() << '\n';
            ++totalNonTrivialCallSites;
            totalCHATargets += CHA.size();
            totalOFATargets += CHA.size();
            return;
        } else {
            OFA = collectVirtualMethods(OFATypes.toClasses(), index.value());
            ++totalNonTrivialCallSites;
            totalCHATargets += CHA.size();
            totalOFATargets += OFA.size();
            return;
            if (CHA.size() > OFA.size()) {
                outs() << "In function " << demangle(callInst->getFunction()->getName().str())
                       << "\n";
                outs() << "At virtual call " << *callInst << "\n";
                outs() << "Class hierarchy analysis (" << CHA.size() << "): ";
                for (const auto fnHash : CHA) {
                    outs() << "\"" << demangle(functionSymbols->getFunctionName(fnHash)) << "\" ";
                }
                outs() << '\n';
                outs() << "Object-flow analysis (" << OFA.size() << "): ";
                for (const auto fnHash : OFA) {
                    outs() << "\"" << demangle(functionSymbols->getFunctionName(fnHash)) << "\" ";
                }
                outs() << '\n';
                outs() << '\n';
            }
        }
    } catch (IncompatibleClusterError &e) {
        outs() << e.what() << " in object-flow analysis in "
               << callInst->getParent()->getParent()->getName() << '\n';
    }
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
    classSymbols = std::make_unique<ClassSymbolManager<ClassSymbol>>();
    functionSymbols = std::make_unique<FunctionSymbolManager<FunctionSymbol>>();
    hierarchy = std::make_unique<ClassHierarchy>(classSymbols.get());
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
    for_each_module([&](const std::string &file, llvm::Module *module) {
        for (const GlobalVariable &variable : module->getGlobalList()) {
            if (variable.hasInitializer()) {
                const std::string name = demangle(variable.getName().str());
                if (name.find("vtable for ") != std::string::npos) {
                    const std::string className = removePrefix(name, "vtable for ");
                    ClassSymbol hash = classSymbols->hashClassName(className);
                    decodeVTable(hash, variable.getInitializer());
                } else if (name.find("typeinfo for ") != std::string::npos) {
                    const std::string className = removePrefix(name, "typeinfo for ");
                    ClassSymbol hash = classSymbols->hashClassName(className);
                    decodeRTTI(hash, variable.getInitializer());
                }
            }
        }
    });

    printTime(start);
    outs() << "Clustering " << hierarchy->classCount() << " classes" << '\n';
    hierarchy->clusterClasses();

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
            if (retType && hierarchy->isPolymorphicPointerType(retType)) {
                try {
                    FunctionObjectFlow flow(hierarchy.get(), classSymbols.get(), functionRetTypes);
                    flow.analyzeFunction(&f);
                    ClassSet OFA = flow.queryRetType();
                    auto className = retType->getPointerElementType()->getStructName();
                    auto hash = classSymbols->hashClassName(className);
                    ClassSet CHA = hierarchy->query(hash);
                    if (!OFA.empty() && OFA.count() < CHA.count()) {
                        functionRetTypes.insert({f.getName().str(), OFA});
                    }
                } catch (IncompatibleClusterError &e) {
                    outs() << e.what() << " in return type analysis in " << f.getName() << '\n';
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
