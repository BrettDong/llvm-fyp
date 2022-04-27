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

#include "ClassSet.h"

#include "ClassHierarchy.h"

#if defined(__x86_64__)
#include <x86intrin.h>
#endif

// Use CPU instructions to accelerate bit manipulation if possible
namespace {

inline int countOnes(std::uint64_t n) {
#if defined(__x86_64__)
    return _popcnt64(n);
#elif defined(__GNUC__) || defined(__clang__)
    return __builtin_popcountll(n);
#else
    int c = 0;
    while (n != 0) {
        c += (n & 1);
        n >>= 1;
    }
    return c;
#endif
}

// Assuming n != 0
inline std::uint64_t countTrailingZeros(std::uint64_t n) {
#if defined(__x86_64__) && defined(__BMI__)
    return _tzcnt_u64(n);
#else
    std::uint64_t c = 0;
    while ((n & 1) == 0) {
        ++c;
        n = n / 2;
    }
    return c;
#endif
}

inline std::uint64_t eraseRightmostOne(std::uint64_t n) {
#if defined(__x86_64__) && defined(__BMI__)
    return _blsr_u64(n);
#else
    return n & (n - 1);
#endif
}
}  // namespace

ClassSet::ClassSet(const ClassHierarchy *classes, int cluster)
    : classes(classes), cluster(cluster) {
    if (cluster != nullCluster) {
        setClusterId(cluster);
    } else {
        bits = 0;
    }
}

constexpr int ClassSet::elems() const {
    if (bits % ElemBits == 0) {
        return bits / ElemBits;
    } else {
        return bits / ElemBits + 1;
    }
}

void ClassSet::setClusterId(int clusterId) {
    cluster = clusterId;
    bits = static_cast<int>(classes->getCluster(cluster).size());
    storage.clear();
    storage.resize(elems(), 0);
}

bool ClassSet::getBit(int i) const { return storage[i / ElemBits] & (identity << (i % ElemBits)); }

void ClassSet::setBit(int i, bool v) {
    if (v) {
        storage[i / ElemBits] |= (identity << (i % ElemBits));
    } else {
        storage[i / ElemBits] &= ~(identity << (i % ElemBits));
    }
}

void ClassSet::insert(ClassSymbol classHash) {
    if (cluster == nullCluster) {
        setClusterId(classes->getClusterOf(classHash));
    }
    if (classes->getClusterOf(classHash) != cluster) {
        throw std::runtime_error("Inserting class from a different cluster");
    }
    setBit(classes->getClusterLocalIndexOf(classHash), true);
}

bool ClassSet::empty() const {
    if (cluster == nullCluster) {
        return true;
    }
    return std::all_of(storage.begin(), storage.end(), [](ElemTy elem) { return elem == 0; });
}

int ClassSet::count() const {
    if (cluster == nullCluster) {
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < elems(); i++) {
        ans += countOnes(storage[i]);
    }
    return ans;
}

std::set<ClassSymbol> ClassSet::toClasses() const {
    std::set<ClassSymbol> answer;
    for (int i = 0; i < elems(); i++) {
        ElemTy x = storage[i];
        while (x != 0) {
            int t = countTrailingZeros(x);
            answer.insert(classes->getCluster(cluster).at(i * ElemBits + t));
            x = eraseRightmostOne(x);
        }
    }
    return answer;
}

bool ClassSet::intersectWith(const ClassSet &rhs) {
    if (rhs.cluster == nullCluster) {
        return false;
    }
    if (cluster == nullCluster) {
        *this = rhs;
        return true;
    }
    bool changed = false;
    for (int i = 0; i < elems(); i++) {
        ElemTy bit_and = storage[i] & rhs.storage[i];
        if (storage[i] != bit_and) {
            storage[i] = bit_and;
            changed = true;
        }
    }
    return changed;
}

bool ClassSet::unionWith(const ClassSet &rhs) {
    if (rhs.cluster == nullCluster) {
        return false;
    }
    if (cluster == nullCluster) {
        *this = rhs;
        return true;
    }
    bool changed = false;
    for (int i = 0; i < elems(); i++) {
        ElemTy bit_or = storage[i] | rhs.storage[i];
        if (storage[i] != bit_or) {
            storage[i] = bit_or;
            changed = true;
        }
    }
    return changed;
}

bool ClassSet::isSubSetOf(const ClassSet &rhs) const {
    if (cluster == nullCluster) {
        return true;
    }
    if (rhs.cluster == nullCluster) {
        return false;
    }
    for (int i = 0; i < elems(); i++) {
        if ((storage[i] | rhs.storage[i]) != rhs.storage[i]) {
            return false;
        }
    }
    return true;
}