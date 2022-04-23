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

using SymbolHashTy = std::uint32_t;

template <typename T = SymbolHashTy>
class SymbolManager {
   protected:
    std::unordered_map<T, std::string> storage;

    static T hashStr(const std::string &str);
    static T hashStr(const llvm::StringRef &str);

    T hashSymbol(const llvm::StringRef &symbol);

    [[nodiscard]] bool exist(const llvm::StringRef &symbol) const;

    [[nodiscard]] std::string getSymbolName(T hash) const;
};

extern template class SymbolManager<SymbolHashTy>;

using ClassSymbol = SymbolHashTy;

template <typename T = ClassSymbol>
class ClassSymbolManager : public SymbolManager<T> {
   public:
    static llvm::StringRef canonicalizeClassName(llvm::StringRef symbol);

    T hashClassName(llvm::StringRef symbol);

    [[nodiscard]] bool existClassName(llvm::StringRef symbol) const;

    [[nodiscard]] std::string getClassName(T hash) const;
};

extern template class ClassSymbolManager<ClassSymbol>;

using FunctionSymbol = SymbolHashTy;

template <typename T = FunctionSymbol>
class FunctionSymbolManager : public SymbolManager<T> {};

extern template class FunctionSymbolManager<FunctionSymbol>;

#endif  // SYMBOLS_H
