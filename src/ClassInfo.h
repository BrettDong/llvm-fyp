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

#pragma once
#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include "Common.hpp"
#include "Symbols.h"

class ClassInfo {
   private:
    std::vector<std::string> vTable;
    std::set<HashTy> parentClasses;
    HashTy hash;
    Symbols *symbols;

   public:
    explicit ClassInfo(HashTy hash, Symbols *symbols) : hash(hash), symbols(symbols) {}

    void decodeVTable(const llvm::Constant *initializer);
    void decodeRTTI(const llvm::Constant *initializer);

    [[nodiscard]] const std::vector<std::string> &getVTable() const { return vTable; }
    [[nodiscard]] const std::set<HashTy> &getParentClasses() const { return parentClasses; }

    [[nodiscard]] std::string dumpVTable() const;
};

#endif  // CLASS_INFO_H