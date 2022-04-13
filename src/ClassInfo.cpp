// Copyright 2022 Binrui Dong
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ClassInfo.h"

#include "Utils.h"

using namespace llvm;

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
                            auto className = removePrefix(name, "typeinfo for ");
                            parentClasses.insert(symbols->hashClassName(className));
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
