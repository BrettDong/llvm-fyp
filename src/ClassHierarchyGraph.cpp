#include "ClassHierarchyGraph.h"

void ClassHierarchyGraph::addRelationship(const std::string &base, const std::string &derived) {
    if (subClasses.count(base) == 0) {
        subClasses[base] = {};
    }
    subClasses[base].insert(derived);
}

std::set<std::string> ClassHierarchyGraph::querySelfWithDerivedClasses(
    const std::string &base) const {
    std::set<std::string> result{base};
    if (subClasses.count(base) == 0) {
        return result;
    }
    for (const std::string &subClass : subClasses.at(base)) {
        result.insert(subClass);
        std::set<std::string> query = querySelfWithDerivedClasses(subClass);
        for (const std::string &subSubClass : query) {
            result.insert(subSubClass);
        }
    }
    return result;
}
