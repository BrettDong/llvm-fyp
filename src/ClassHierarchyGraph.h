#pragma once
#ifndef CLASS_HIERARCHY_GRAPH_H
#define CLASS_HIERARCHY_GRAPH_H

#include "Common.hpp"

class ClassHierarchyGraph {
   private:
    std::map<std::string, std::set<std::string>> subClasses;

   public:
    void addRelationship(const std::string &base, const std::string &derived);
    std::set<std::string> querySelfWithDerivedClasses(const std::string &base) const;
};

#endif  // CLASS_HIERARCHY_GRAPH_H
