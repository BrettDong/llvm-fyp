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

#include "ClassHierarchy.h"

void ClassHierarchy::addRelation(ClassSymbol base, ClassSymbol derived) {
    subClasses[base].insert(derived);
    classes.insert(base);
    classes.insert(derived);
}

void ClassHierarchy::clusterClasses() {
    std::map<ClassSymbol, std::set<ClassSymbol>> edges;
    for (const auto &[base, derivedClasses] : subClasses) {
        for (const auto derived : derivedClasses) {
            edges[base].insert(derived);
            edges[derived].insert(base);
        }
    }

    int nextClusterNo = 0;
    for (const auto hash : classes) {
        if (clusterOf.count(hash) > 0) {
            continue;
        }
        const int currentCluster = nextClusterNo++;
        clusters.emplace_back(std::vector<ClassSymbol>());
        int localIndex = 0;
        std::queue<ClassSymbol> q;
        q.push(hash);
        while (!q.empty()) {
            ClassSymbol cur = q.front();
            q.pop();
            clusterOf[cur] = currentCluster;
            classLocalIndex[cur] = localIndex++;
            clusters[currentCluster].emplace_back(cur);
            for (const auto adj : edges[cur]) {
                if (clusterOf.count(adj) == 0) {
                    q.push(adj);
                }
            }
        }
    }
}

bool ClassHierarchy::isPolymorphicClass(const llvm::StringRef &name) const {
    if (!symbols->existClassName(name)) {
        return false;
    }
    auto hash = symbols->hashClassName(name);
    return classes.count(hash) > 0;
}

bool ClassHierarchy::isPolymorphicPointerType(llvm::Type *type) const {
    if (type->isPointerTy() && type->getPointerElementType()->isStructTy()) {
        auto name = type->getPointerElementType()->getStructName();
        return isPolymorphicClass(name);
    } else {
        return false;
    }
}

ClassSet ClassHierarchy::query(ClassSymbol classHash) {
    if (hierarchyCache.count(classHash) > 0) {
        return hierarchyCache.at(classHash);
    }

    ClassSet result(this, clusterOf.at(classHash));
    std::queue<ClassSymbol> q;
    q.push(classHash);

    while (!q.empty()) {
        ClassSymbol cur = q.front();
        q.pop();
        result.insert(cur);
        if (subClasses.count(cur) > 0) {
            for (const ClassSymbol subClass : subClasses.at(cur)) {
                q.push(subClass);
            }
        }
    }

    hierarchyCache.insert({classHash, result});
    return result;
}
