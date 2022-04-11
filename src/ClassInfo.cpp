#include "ClassInfo.h"

#include "Utils.h"

void ClassInfo::decodeVTable(const Constant *initializer) {
    if (!vTable.empty()) {
        return;
    }
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
                            Value *operand = cast->getOperand(0);
                            if (auto *f = dyn_cast<Function>(operand)) {
                                vTable.push_back(f->getName().str());
                            } else if (auto *a = dyn_cast<GlobalAlias>(operand)) {
                                if (auto *af = dyn_cast<Function>(a->getAliasee())) {
                                    vTable.push_back(af->getName().str());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void ClassInfo::decodeRTTI(const Constant *initializer) {
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
                            parentClasses.insert(removePrefix(name, "typeinfo for "));
                        }
                    }
                }
            }
        }
    }
}

std::string ClassInfo::dumpVTable() const {
    std::ostringstream oss;
    for (const auto &entry : vTable) {
        oss << '"' << demangle(entry) << '"' << ", ";
    }
    std::string str = oss.str();
    if (str.size() > 2) {
        str.erase(str.end() - 2, str.end());
    }
    return str;
}
