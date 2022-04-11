#include "ClassAnalyzer.h"

#include "Utils.h"

bool ClassAnalyzer::isPolymorphicType(const llvm::Type *ty) const {
    if (ty->isPointerTy() && ty->getPointerElementType()->isStructTy()) {
        auto className = stripClassName(ty->getPointerElementType()->getStructName().str());
        return classes.count(className) != 0;
    } else {
        return false;
    }
}

bool ClassAnalyzer::isClassExist(const std::string &className) const {
    return classes.count(className) != 0;
}

const ClassInfo &ClassAnalyzer::getClass(const std::string &className) const {
    return classes.at(className);
}

void ClassAnalyzer::analyzeModule(Module *module) {
    for (const GlobalVariable &variable : module->getGlobalList()) {
        if (variable.hasInitializer()) {
            const std::string name = demangle(variable.getName().str());
            if (name.find("vtable for ") != std::string::npos) {
                const std::string className = removePrefix(name, "vtable for ");
                if (classes.count(className) == 0) {
                    classes.insert({className, ClassInfo(className)});
                }
                classes.at(className).decodeVTable(variable.getInitializer());
            }
        }
    }

    for (const GlobalVariable &variable : module->getGlobalList()) {
        if (variable.hasInitializer()) {
            const std::string name = demangle(variable.getName().str());
            if (name.find("typeinfo for ") != std::string::npos) {
                const std::string className = removePrefix(name, "typeinfo for ");
                if (classes.count(className) == 0) {
                    classes.insert({className, ClassInfo(className)});
                }
                classes.at(className).decodeRTTI(variable.getInitializer());
            }
        }
    }
}

void ClassAnalyzer::buildClassHierarchyGraph() {
    for (const auto &it : classes) {
        if (it.second.getParentClasses().empty()) {
            continue;
        }
        for (const string &parent : it.second.getParentClasses()) {
            hierarchy.addRelationship(parent, it.first);
        }
    }
}
