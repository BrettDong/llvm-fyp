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
#ifndef CLASS_SET_H
#define CLASS_SET_H

#include "Common.hpp"
#include "Symbols.h"

class ClassAnalyzer;

class ClassSet {
   private:
    using ElemTy = std::uint64_t;
    static constexpr int ElemBits = sizeof(ElemTy) * 8;
    static constexpr ElemTy identity = static_cast<ElemTy>(1);

    static constexpr int nullCluster = -1;

    const ClassAnalyzer *classes;
    int cluster;
    int bits;
    int elems;
    llvm::SmallVector<ElemTy> storage;

    void setClusterId(int clusterId);

   public:
    explicit ClassSet(const ClassAnalyzer *classes);

    explicit ClassSet(const ClassAnalyzer *classes, int cluster);

    ClassSet(const ClassSet &rhs) = default;

    [[nodiscard]] bool getBit(int i) const;

    void setBit(int i, bool v);

    void insert(HashTy classHash);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] int count() const;

    [[nodiscard]] std::set<HashTy> toClasses() const;

    // intersect this to rhs, return true if value is changed
    bool intersectWith(const ClassSet &rhs);

    // union this to rhs, return true if value is changed
    bool unionWith(const ClassSet &rhs);

    [[nodiscard]] bool isSubSetOf(const ClassSet &rhs) const;
};

#endif  // CLASS_SET_H
