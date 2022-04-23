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
    std::map<ClassSymbol, ClassInfo> classes;
    std::map<ClassSymbol, int> classToCluster;
    std::map<ClassSymbol, int> classLocalIndex;
    std::map<int, std::vector<ClassSymbol>> clusters;
    std::map<ClassSymbol, ClassSet> subClasses;
    std::map<ClassSymbol, ClassSet> hierarchyCache;
    ClassSymbolManager<ClassSymbol> *symbols;

   public:
    explicit ClassAnalyzer(ClassSymbolManager<ClassSymbol> *symbols) : symbols(symbols) {}

    [[nodiscard]] bool isPolymorphicType(llvm::StringRef name) const;
    [[nodiscard]] bool isPolymorphicType(const llvm::Type *ty) const;

    [[nodiscard]] size_t classCount() const { return classes.size(); }
    [[nodiscard]] size_t clusterCount() const { return clusters.size(); }

    [[nodiscard]] const ClassInfo &getClass(ClassSymbol classHash) const {
        return classes.at(classHash);
    }

    [[nodiscard]] int clusterOf(ClassSymbol classHash) const {
        return classToCluster.at(classHash);
    }

    [[nodiscard]] int clusterLocalIndexOf(ClassSymbol classHash) const {
        return classLocalIndex.at(classHash);
    }

    [[nodiscard]] const std::vector<ClassSymbol> &getCluster(int cluster) const {
        return clusters.at(cluster);
    };

    void analyzeModule(llvm::Module *m);

    void clusterClasses();

    void buildClassHierarchyGraph();

    [[nodiscard]] ClassSet getSelfAndDerivedClasses(ClassSymbol classHash);

    [[nodiscard]] const std::map<ClassSymbol, ClassInfo> &getAllClasses() const { return classes; }
};

#endif  // CLASS_ANALYZER_H
