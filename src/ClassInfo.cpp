#include "ClassInfo.h"

#include "Utils.h"

void ClassInfo::decodeVTable(const Constant *initializer) {
    if (vtable) return;
    vtable = std::make_unique<VTable>(initializer);
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

VTable *ClassInfo::getVTable() const {
    if (vtable) {
        return vtable.get();
    } else {
        return nullptr;
    }
}

const std::set<std::string> &ClassInfo::getParentClasses() const { return parentClasses; }
