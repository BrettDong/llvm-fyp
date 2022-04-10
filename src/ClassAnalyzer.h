#pragma once
#ifndef CLASS_ANALYZER_H
#define CLASS_ANALYZER_H

#include "ClassHierarchyGraph.h"
#include "ClassInfo.h"
#include "Common.hpp"

class ClassAnalyzer {
   private:
    std::map<std::string, ClassInfo> classes;
    ClassHierarchyGraph hierarchy;

   public:
    [[nodiscard]] bool isClassExist(const std::string &className) const;
    [[nodiscard]] const ClassInfo &getClass(const std::string &className) const;

    void analyzeModule(Module *m);

    void buildClassHierarchyGraph();

    [[nodiscard]] const std::map<std::string, ClassInfo> &getAllClasses() const { return classes; }
    [[nodiscard]] const ClassHierarchyGraph &getHierarchyGraph() const { return hierarchy; }
};

#endif  // CLASS_ANALYZER_H
