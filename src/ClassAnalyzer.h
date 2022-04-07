#pragma once
#ifndef CLASS_ANALYZER_H
#define CLASS_ANALYZER_H

#include "ClassHierarchyGraph.h"
#include "ClassInfo.h"
#include "Common.hpp"
#include "VTable.h"

class ClassAnalyzer {
   private:
    std::map<std::string, ClassInfo> classes;
    ClassHierarchyGraph hierarchy;

   public:
    [[nodiscard]] const ClassInfo &getClass(const std::string &className) const;

    void analyzeModule(Module *m);

    void buildClassHierarchyGraph();

    const ClassHierarchyGraph &getHierarchyGraph() const { return hierarchy; }
};

#endif  // CLASS_ANALYZER_H
