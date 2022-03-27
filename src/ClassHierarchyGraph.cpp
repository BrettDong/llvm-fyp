#include "ClassHierarchyGraph.h"

void ClassHierarchyGraph::addRelationship(const std::string &base, const std::string &derived) {
    if (subClasses.count(base) == 0) {
        subClasses[base] = set<string>();
    }
    subClasses[base].insert(derived);
}

set<string> ClassHierarchyGraph::queryDerivedClasses(const std::string &base) const {
    set<string> result;
    if (subClasses.count(base) == 0) {
        return result;
    }
    for (const std::string &subClass : subClasses.at(base)) {
        result.insert(subClass);
        set<string> query = queryDerivedClasses(subClass);
        for (const std::string &subSubClass : query) {
            result.insert(subSubClass);
        }
    }
    return result;
}
