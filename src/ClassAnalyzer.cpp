#include "ClassAnalyzer.h"

#include "Symbols.h"
#include "Utils.h"

using namespace llvm;

bool ClassAnalyzer::isPolymorphicType(llvm::StringRef name) const {
    return symbols->exist(name) && classes.count(symbols->hashClassName(name));
}

bool ClassAnalyzer::isPolymorphicType(const llvm::Type *ty) const {
    if (ty->isPointerTy() && ty->getPointerElementType()->isStructTy()) {
        auto name = ty->getPointerElementType()->getStructName();
        return isPolymorphicType(name);
    } else {
        return false;
    }
}

const ClassInfo &ClassAnalyzer::getClass(HashTy classHash) const { return classes.at(classHash); }

void ClassAnalyzer::analyzeModule(Module *module) {
    for (const GlobalVariable &variable : module->getGlobalList()) {
        if (variable.hasInitializer()) {
            const std::string name = demangle(variable.getName().str());
            if (name.find("vtable for ") != std::string::npos) {
                const std::string className = removePrefix(name, "vtable for ");
                HashTy hash = symbols->hashClassName(className);
                if (classes.count(hash) == 0) {
                    classes.insert({hash, ClassInfo(hash, symbols)});
                }
                classes.at(hash).decodeVTable(variable.getInitializer());
            }
        }
    }

    for (const GlobalVariable &variable : module->getGlobalList()) {
        if (variable.hasInitializer()) {
            const std::string name = demangle(variable.getName().str());
            if (name.find("typeinfo for ") != std::string::npos) {
                const std::string className = removePrefix(name, "typeinfo for ");
                HashTy hash = symbols->hashClassName(className);
                if (classes.count(hash) == 0) {
                    classes.insert({hash, ClassInfo(hash, symbols)});
                }
                classes.at(hash).decodeRTTI(variable.getInitializer());
            }
        }
    }
}

void ClassAnalyzer::clusterClasses() {
    std::map<HashTy, std::set<HashTy>> edges;
    for (const auto &[hash, info] : classes) {
        for (const auto &parent : info.getParentClasses()) {
            edges[hash].insert(parent);
            edges[parent].insert(hash);
        }
    }

    int nextClusterNo = 0;
    for (const auto &[hash, info] : classes) {
        if (classToCluster.count(hash) > 0) {
            continue;
        }
        const int currentCluster = nextClusterNo++;
        std::queue<HashTy> q;
        q.push(hash);
        while (!q.empty()) {
            HashTy cur = q.front();
            q.pop();
            classToCluster[cur] = currentCluster;
            clusters[currentCluster].insert(cur);
            for (const auto adj : edges[cur]) {
                if (classToCluster.count(adj) == 0) {
                    q.push(adj);
                }
            }
        }
    }
}

void ClassAnalyzer::buildClassHierarchyGraph() {
    for (const auto &[hash, info] : classes) {
        for (const HashTy parentHash : info.getParentClasses()) {
            subClasses[parentHash].insert(hash);
        }
    }
}

std::set<HashTy> ClassAnalyzer::getSelfAndDerivedClasses(HashTy classHash) const {
    std::set<HashTy> result{classHash};
    if (subClasses.count(classHash) == 0) {
        return result;
    }
    for (const HashTy subClass : subClasses.at(classHash)) {
        result.insert(subClass);
        std::set<HashTy> query = getSelfAndDerivedClasses(subClass);
        for (const HashTy subSubClass : query) {
            result.insert(subSubClass);
        }
    }
    return result;
}
