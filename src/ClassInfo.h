#pragma once
#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include "Common.hpp"
#include "Symbols.h"

class ClassInfo {
   private:
    std::vector<std::string> vTable;
    std::set<std::string> parentClasses;
    std::string className;
    Symbols *symbols;

   public:
    explicit ClassInfo(const std::string &className, Symbols *symbols)
        : className(className), symbols(symbols) {}

    void decodeVTable(const llvm::Constant *initializer);
    void decodeRTTI(const llvm::Constant *initializer);

    [[nodiscard]] const std::vector<std::string> &getVTable() const { return vTable; }
    [[nodiscard]] const std::set<std::string> &getParentClasses() const { return parentClasses; }

    [[nodiscard]] std::string dumpVTable() const;
};

#endif  // CLASS_INFO_H