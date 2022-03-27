#include "ModuleReader.h"

#include "Utils.h"

void ModuleReader::addClassMethod(const string &className, const string &functionName) {
    if (classMethods.count(className) == 0) {
        classMethods[className] = set<string>();
    }
    classMethods[className].insert(functionName);
}

void ModuleReader::addClassParent(const string &className, const string &parentClassName) {
    if (classParents.count(className) == 0) {
        classParents[className] = set<string>();
    }
    classParents[className].insert(parentClassName);
}

void ModuleReader::decodeVTable(const std::string &className, const Constant *initializer) {
    const auto *aggregate = dyn_cast<ConstantAggregate>(initializer);
    if (aggregate == nullptr) {
        return;
    }
    for (size_t i = 0; i < aggregate->getNumOperands(); i++) {
        if (const auto *array = dyn_cast<ConstantArray>(aggregate->getAggregateElement(i))) {
            for (size_t j = 0; j < array->getNumOperands(); j++) {
                if (auto *expr = dyn_cast<ConstantExpr>(array->getAggregateElement(j))) {
                    if (expr->isCast()) {
                        auto *constant = dyn_cast<Constant>(expr);
                        if (Constant *cast = ConstantExpr::getBitCast(constant, expr->getType())) {
                            if (auto *f = dyn_cast<Function>(cast->getOperand(0))) {
                                std::string functionName = demangle(f->getName().str());
                                addClassMethod(className, functionName);
                            }
                        }
                    }
                }
            }
        }
    }
}

void ModuleReader::decodeRTTI(const std::string &className, const Constant *initializer) {
    const auto *aggregate = dyn_cast<ConstantAggregate>(initializer);
    if (aggregate == nullptr) {
        return;
    }
    for (size_t i = 0; i < aggregate->getNumOperands(); i++) {
        if (auto *expr = dyn_cast<ConstantExpr>(aggregate->getAggregateElement(i))) {
            if (expr->isCast()) {
                auto *constant = dyn_cast<Constant>(expr);
                if (Constant *cast = ConstantExpr::getBitCast(constant, expr->getType())) {
                    if (auto *v = dyn_cast<GlobalVariable>(cast->getOperand(0))) {
                        std::string name = demangle(v->getName().str());
                        if (beginsWith(name, "typeinfo for ")) {
                            addClassParent(className, removePrefix(name, "typeinfo for "));
                        }
                    }
                }
            }
        }
    }
}

void ModuleReader::analyzeModule(Module *module) {
    for (const GlobalVariable &variable : module->getGlobalList()) {
        if (variable.hasInitializer()) {
            const std::string name = demangle(variable.getName().str());
            if (name.find("vtable for ") != std::string::npos) {
                const std::string className = removePrefix(name, "vtable for ");
                classNames.insert(className);
                decodeVTable(className, variable.getInitializer());
            }
        }
    }

    for (const GlobalVariable &variable : module->getGlobalList()) {
        if (variable.hasInitializer()) {
            const std::string name = demangle(variable.getName().str());
            if (name.find("typeinfo for ") != std::string::npos) {
                const std::string className = removePrefix(name, "typeinfo for ");
                if (classNames.count(className) > 0) {
                    decodeRTTI(className, variable.getInitializer());
                }
            }
        }
    }
}

void ModuleReader::dump() {
    for (const string &className : classNames) {
        outs() << "class " << className << "\n";
        for (const string &parent : classParents[className]) {
            outs() << "  parent class " << parent << "\n";
        }
        for (const string &method : classMethods[className]) {
            outs() << "  member function " << method << "\n";
        }
        outs() << "\n";
    }
}
