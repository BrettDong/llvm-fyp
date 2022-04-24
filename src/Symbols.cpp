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

#include "Symbols.h"

template <typename T>
T SymbolManager<T>::hashStr(const std::string& str) {
    T hash = 5381;
    for (auto c : str) {
        hash = hash * 33 + c;
    }
    return hash;
}

template <typename T>
T SymbolManager<T>::hashStr(const llvm::StringRef& str) {
    T hash = 5381;
    for (auto c : str) {
        hash = hash * 33 + c;
    }
    return hash;
}

template <typename T>
T SymbolManager<T>::hashSymbol(const llvm::StringRef& symbol) {
    T hash = hashStr(symbol);
    while (storage.count(hash) != 0) {
        if (storage[hash] == symbol) {
            return hash;
        }
        ++hash;
    }
    storage[hash] = symbol.str();
    return hash;
}

template <typename T>
bool SymbolManager<T>::exist(const llvm::StringRef& symbol) const {
    T hash = hashStr(symbol);
    while (storage.count(hash) != 0) {
        if (storage.at(hash) == symbol) {
            return true;
        }
        ++hash;
    }
    return false;
}

template <typename T>
std::string SymbolManager<T>::getSymbolName(T hash) const {
    auto it = storage.find(hash);
    if (it != storage.end()) {
        return it->second;
    }
    return {};
}

template class SymbolManager<SymbolHashTy>;

template <typename T>
llvm::StringRef ClassSymbolManager<T>::canonicalizeClassName(llvm::StringRef symbol) {
    static const llvm::StringRef classPrefix = "class.";
    static const llvm::StringRef structPrefix = "struct.";

    if (symbol.startswith(classPrefix)) {
        symbol = symbol.drop_front(classPrefix.size());
    } else if (symbol.startswith(structPrefix)) {
        symbol = symbol.drop_front(structPrefix.size());
    }

    size_t dot = 0;
    while (((dot = symbol.rfind('.')) != llvm::StringRef::npos) &&
           std::all_of(symbol.begin() + dot + 1, symbol.end(), isdigit)) {
        symbol = symbol.take_front(dot);
    }

    return symbol;
}

template <typename T>
T ClassSymbolManager<T>::hashClassName(llvm::StringRef symbol) {
    return SymbolManager<T>::hashSymbol(canonicalizeClassName(symbol));
}

template <typename T>
bool ClassSymbolManager<T>::existClassName(llvm::StringRef symbol) const {
    return SymbolManager<T>::exist(canonicalizeClassName(symbol));
}

template <typename T>
std::string ClassSymbolManager<T>::getClassName(T hash) const {
    return SymbolManager<T>::getSymbolName(hash);
}

template class ClassSymbolManager<ClassSymbol>;

template <typename T>
T FunctionSymbolManager<T>::hashFunctionName(const llvm::StringRef& symbol) {
    return SymbolManager<T>::hashSymbol(symbol);
}

template <typename T>
std::string FunctionSymbolManager<T>::getFunctionName(T hash) const {
    return SymbolManager<T>::getSymbolName(hash);
}

template class FunctionSymbolManager<FunctionSymbol>;
