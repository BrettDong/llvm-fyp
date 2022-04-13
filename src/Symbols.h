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
#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "Common.hpp"

using HashTy = std::uint32_t;

class Symbols {
   private:
    std::map<HashTy, std::string> storage;

    static HashTy hashStr(const std::string &str);
    static HashTy hashStr(const llvm::StringRef &str);

   public:
    static llvm::StringRef canonicalizeClassName(llvm::StringRef symbol);

    HashTy hashClassName(llvm::StringRef symbol);

    bool exist(llvm::StringRef symbol) const;

    [[nodiscard]] std::string getClassName(HashTy hash) const;
};

#endif  // SYMBOLS_H
