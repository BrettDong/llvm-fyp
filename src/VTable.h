#pragma once
#ifndef VTABLE_H
#define VTABLE_H

#include "Common.hpp"

class VTable {
   private:
    std::vector<llvm::Function *> entries;

   public:
    explicit VTable(const Constant *initializer);

    [[nodiscard]] const std::vector<llvm::Function *> &getAllEntries() const;
    [[nodiscard]] llvm::Function *getEntry(std::size_t index) const;

    bool operator==(const VTable &rhs) const;
};

#endif  // VTABLE_H