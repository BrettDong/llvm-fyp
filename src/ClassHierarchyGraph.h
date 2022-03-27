#pragma once
#ifndef CLASS_HIERARCHY_GRAPH_H
#define CLASS_HIERARCHY_GRAPH_H

#include "Common.hpp"

class ClassHierarchyGraph {
   private:
    map<string, set<string>> subClasses;

   public:
    void addRelationship(const std::string &base, const std::string &derived);
    set<string> queryDerivedClasses(const std::string &base) const;
};

#endif  // CLASS_HIERARCHY_GRAPH_H
