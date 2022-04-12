#include "Symbols.h"

HashTy Symbols::hashStr(const std::string& str) {
    HashTy hash = 5381;
    for (auto c : str) {
        hash = hash * 33 + c;
    }
    return hash;
}

HashTy Symbols::hashStr(const llvm::StringRef& str) {
    HashTy hash = 5381;
    for (auto c : str) {
        hash = hash * 33 + c;
    }
    return hash;
}

llvm::StringRef Symbols::canonicalizeClassName(llvm::StringRef symbol) {
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

HashTy Symbols::hashClassName(llvm::StringRef symbol) {
    llvm::StringRef canonical = canonicalizeClassName(symbol);
    HashTy hash = hashStr(canonical);
    while (storage.count(hash) != 0) {
        if (storage[hash] == canonical) {
            return hash;
        }
        ++hash;
    }
    storage[hash] = canonical.str();
    return hash;
}

std::string Symbols::getClassName(HashTy hash) const {
    auto it = storage.find(hash);
    if (it != storage.end()) {
        return it->second;
    }
    return {};
}
