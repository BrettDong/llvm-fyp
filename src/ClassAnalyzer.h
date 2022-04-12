#pragma once
#ifndef CLASS_ANALYZER_H
#define CLASS_ANALYZER_H

#include "ClassHierarchyGraph.h"
#include "ClassInfo.h"
#include "Common.hpp"
#include "Symbols.h"

class ClassAnalyzer {
   private:
    std::map<std::string, ClassInfo> classes;
    ClassHierarchyGraph hierarchy;
    Symbols *symbols;

   public:
    explicit ClassAnalyzer(Symbols *symbols) : symbols(symbols) {}

    [[nodiscard]] bool isPolymorphicType(const llvm::Type *ty) const;
    [[nodiscard]] bool isClassExist(const std::string &className) const;
    [[nodiscard]] const ClassInfo &getClass(const std::string &className) const;

    void analyzeModule(llvm::Module *m);

    void buildClassHierarchyGraph();

    [[nodiscard]] const std::map<std::string, ClassInfo> &getAllClasses() const { return classes; }
    [[nodiscard]] const ClassHierarchyGraph &getHierarchyGraph() const { return hierarchy; }
};

#endif  // CLASS_ANALYZER_H
