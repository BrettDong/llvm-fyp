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

#include "ClassAnalyzer.h"

#include "ClassSet.h"
#include "Symbols.h"
#include "Utils.h"

using namespace llvm;

bool ClassAnalyzer::isPolymorphicType(llvm::StringRef name) const {
    return symbols->existClassName(name) && classes.count(symbols->hashClassName(name));
}

bool ClassAnalyzer::isPolymorphicType(const llvm::Type *ty) const {
    if (ty->isPointerTy() && ty->getPointerElementType()->isStructTy()) {
        auto name = ty->getPointerElementType()->getStructName();
        return isPolymorphicType(name);
    } else {
        return false;
    }
}

void ClassAnalyzer::analyzeModule(Module *module) {
    for (const GlobalVariable &variable : module->getGlobalList()) {
        if (variable.hasInitializer()) {
            const std::string name = demangle(variable.getName().str());
            if (name.find("vtable for ") != std::string::npos) {
                const std::string className = removePrefix(name, "vtable for ");
                ClassSymbol hash = symbols->hashClassName(className);
                if (classes.count(hash) == 0) {
                    classes.insert({hash, ClassInfo(hash, symbols)});
                }
                classes.at(hash).decodeVTable(variable.getInitializer());
            }
        }
    }

    for (const GlobalVariable &variable : module->getGlobalList()) {
        if (variable.hasInitializer()) {
            const std::string name = demangle(variable.getName().str());
            if (name.find("typeinfo for ") != std::string::npos) {
                const std::string className = removePrefix(name, "typeinfo for ");
                ClassSymbol hash = symbols->hashClassName(className);
                if (classes.count(hash) == 0) {
                    classes.insert({hash, ClassInfo(hash, symbols)});
                }
                classes.at(hash).decodeRTTI(variable.getInitializer());
            }
        }
    }
}

void ClassAnalyzer::clusterClasses() {
    std::map<ClassSymbol, std::set<ClassSymbol>> edges;
    for (const auto &[hash, info] : classes) {
        for (const auto &parent : info.getParentClasses()) {
            edges[hash].insert(parent);
            edges[parent].insert(hash);
        }
    }

    int nextClusterNo = 0;
    for (const auto &[hash, info] : classes) {
        if (classToCluster.count(hash) > 0) {
            continue;
        }
        const int currentCluster = nextClusterNo++;
        int localIndex = 0;
        std::queue<ClassSymbol> q;
        q.push(hash);
        while (!q.empty()) {
            ClassSymbol cur = q.front();
            q.pop();
            classToCluster[cur] = currentCluster;
            classLocalIndex[cur] = localIndex++;
            clusters[currentCluster].emplace_back(cur);
            for (const auto adj : edges[cur]) {
                if (classToCluster.count(adj) == 0) {
                    q.push(adj);
                }
            }
        }
    }
}

void ClassAnalyzer::buildClassHierarchyGraph() {
    for (const auto &[hash, info] : classes) {
        for (const ClassSymbol parentHash : info.getParentClasses()) {
            if (subClasses.count(parentHash) == 0) {
                subClasses.insert({parentHash, ClassSet(this, clusterOf(parentHash))});
            }
            subClasses.at(parentHash).insert(hash);
        }
    }
}

ClassSet ClassAnalyzer::getSelfAndDerivedClasses(ClassSymbol classHash) {
    if (hierarchyCache.count(classHash) > 0) {
        return hierarchyCache.at(classHash);
    }

    ClassSet result(this, classToCluster.at(classHash));
    std::queue<ClassSymbol> q;
    q.push(classHash);

    while (!q.empty()) {
        ClassSymbol cur = q.front();
        q.pop();
        result.insert(cur);
        if (subClasses.count(cur) > 0) {
            for (const ClassSymbol subClass : subClasses.at(cur).toClasses()) {
                q.push(subClass);
            }
        }
    }

    hierarchyCache.insert({classHash, result});
    return result;
}
