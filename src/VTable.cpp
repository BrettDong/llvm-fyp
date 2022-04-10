#include "VTable.h"

#include "Common.hpp"

VTable::VTable(const Constant *initializer) {
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
                                entries.push_back(f);
                            }
                        }
                    }
                }
            }
        }
    }
}

const std::vector<llvm::Function *> &VTable::getAllEntries() const { return entries; }

llvm::Function *VTable::getEntry(std::size_t index) const {
    if (index >= entries.size()) {
        return nullptr;
    } else {
        return entries.at(index);
    }
}

bool VTable::operator==(const VTable &rhs) const {
    if (entries.size() != rhs.entries.size()) return false;
    for (size_t i = 0; i < entries.size(); i++) {
        if (entries[i]->getName() != rhs.entries[i]->getName()) {
            errs() << "This have " << entries[i]->getName() << '\n';
            errs() << "RHS  have " << rhs.entries[i]->getName() << '\n';
            return false;
        }
    }
    return true;
}