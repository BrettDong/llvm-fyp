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