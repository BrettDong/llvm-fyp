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
#ifndef CLASS_ANALYZER_H
#define CLASS_ANALYZER_H

#include "ClassInfo.h"
#include "ClassSet.h"
#include "Common.hpp"
#include "Symbols.h"

class ClassAnalyzer {
   private:
    std::map<HashTy, ClassInfo> classes;
    std::map<HashTy, int> classToCluster;
    std::map<HashTy, int> classLocalIndex;
    std::map<int, std::vector<HashTy>> clusters;
    std::map<HashTy, std::set<HashTy>> subClasses;
    Symbols *symbols;

   public:
    explicit ClassAnalyzer(Symbols *symbols) : symbols(symbols) {}

    [[nodiscard]] bool isPolymorphicType(llvm::StringRef name) const;
    [[nodiscard]] bool isPolymorphicType(const llvm::Type *ty) const;

    [[nodiscard]] size_t classCount() const { return classes.size(); }
    [[nodiscard]] size_t clusterCount() const { return clusters.size(); }

    [[nodiscard]] const ClassInfo &getClass(HashTy classHash) const {
        return classes.at(classHash);
    }

    [[nodiscard]] int clusterOf(HashTy classHash) const { return classToCluster.at(classHash); }

    [[nodiscard]] int clusterLocalIndexOf(HashTy classHash) const {
        return classLocalIndex.at(classHash);
    }

    [[nodiscard]] const std::vector<HashTy> &getCluster(int cluster) const {
        return clusters.at(cluster);
    };

    void analyzeModule(llvm::Module *m);

    void clusterClasses();

    void buildClassHierarchyGraph();

    [[nodiscard]] ClassSet getSelfAndDerivedClasses(HashTy classHash) const;

    [[nodiscard]] const std::map<HashTy, ClassInfo> &getAllClasses() const { return classes; }
};

#endif  // CLASS_ANALYZER_H
