#pragma once
#ifndef CLASS_SET_H
#define CLASS_SET_H

#include "ClassAnalyzer.h"
#include "Common.hpp"

class ClassSet {
   private:
    using ElemTy = std::uint64_t;
    static constexpr int ElemBits = sizeof(ElemTy) * 8;
    static constexpr ElemTy identity = static_cast<ElemTy>(1);

    ClassAnalyzer *classes;
    const int cluster;
    int bits;
    llvm::SmallVector<ElemTy> storage;

   public:
    explicit ClassSet(ClassAnalyzer *classes, int cluster);

    bool getBit(int i) const;

    void setBit(int i, bool v);

    std::set<HashTy> toClasses() const;
};

#endif  // CLASS_SET_H
