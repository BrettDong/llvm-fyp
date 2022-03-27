#pragma once
#ifndef CLASS_ANALYZER_H
#define CLASS_ANALYZER_H

#include "ClassHierarchyGraph.h"
#include "Common.hpp"

class ClassAnalyzer {
   private:
    set<string> classNames;
    map<string, set<string>> classMethods;
    map<string, set<string>> classParents;

    void addClassMethod(const std::string &className, const std::string &functionName);
    void addClassParent(const std::string &className, const std::string &parentClassName);

    void decodeVTable(const std::string &className, const Constant *initializer);
    void decodeRTTI(const std::string &className, const Constant *initializer);

   public:
    [[nodiscard]] const set<string> &getClasses() const;
    [[nodiscard]] const set<string> &getMethodsOfClass(const std::string &className) const;

    void analyzeModule(Module *m);
    void dump();
    [[nodiscard]] ClassHierarchyGraph buildClassHierarchyGraph() const;
};

#endif  // CLASS_ANALYZER_H
