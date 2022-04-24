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

#pragma once
#ifndef CLASS_HIERARCHY_H
#define CLASS_HIERARCHY_H

#include "ClassSet.h"
#include "Symbols.h"

class ClassHierarchy {
   private:
    // ClassSymbol -> the cluster ID it belongs to
    std::unordered_map<ClassSymbol, int> clusterOf;

    // ClassSymbol -> the index in its belonging cluster
    std::unordered_map<ClassSymbol, int> classLocalIndex;

    // ClassSymbols of each class cluster
    std::vector<std::vector<ClassSymbol>> clusters;

    std::set<ClassSymbol> classes;

    // Base -> Derived relationships
    std::unordered_map<ClassSymbol, std::set<ClassSymbol>> subClasses;

    // Cached class hierarchy analysis
    std::unordered_map<ClassSymbol, ClassSet> hierarchyCache;

    ClassSymbolManager<ClassSymbol> *symbols;

   public:
    explicit ClassHierarchy(ClassSymbolManager<ClassSymbol> *symbols) : symbols(symbols) {}

    void addRelation(ClassSymbol base, ClassSymbol derived);

    void clusterClasses();

    [[nodiscard]] size_t classCount() const { return classes.size(); }

    [[nodiscard]] size_t clusterCount() const { return clusters.size(); }

    [[nodiscard]] int getClusterOf(ClassSymbol classHash) const { return clusterOf.at(classHash); }

    [[nodiscard]] int getClusterLocalIndexOf(ClassSymbol classHash) const {
        return classLocalIndex.at(classHash);
    }

    [[nodiscard]] const std::vector<ClassSymbol> &getCluster(int cluster) const {
        return clusters.at(cluster);
    };

    [[nodiscard]] bool isPolymorphicClass(const llvm::StringRef &name) const;

    [[nodiscard]] bool isPolymorphicPointerType(llvm::Type *type) const;

    [[nodiscard]] ClassSet query(ClassSymbol classHash);
};

#endif  // CLASS_HIERARCHY_H
