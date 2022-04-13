#pragma once
#ifndef CLASS_ANALYZER_H
#define CLASS_ANALYZER_H

#include "ClassInfo.h"
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

    std::set<HashTy> getSelfAndDerivedClasses(HashTy classHash) const;

    [[nodiscard]] const std::map<HashTy, ClassInfo> &getAllClasses() const { return classes; }
};

#endif  // CLASS_ANALYZER_H
