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
