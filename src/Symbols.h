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

    [[nodiscard]] std::string getClassName(HashTy hash) const;
};

#endif  // SYMBOLS_H
