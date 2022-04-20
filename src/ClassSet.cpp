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

#include "ClassAnalyzer.h"

ClassSet::ClassSet(const ClassAnalyzer *classes) : classes(classes), cluster(nullCluster) {
    bits = 0;
    elems = 0;
}

ClassSet::ClassSet(const ClassAnalyzer *classes, int cluster) : classes(classes) {
    setClusterId(cluster);
}

void ClassSet::setClusterId(int clusterId) {
    cluster = clusterId;
    bits = static_cast<int>(classes->getCluster(cluster).size());
    if (bits % ElemBits == 0) {
        elems = bits / ElemBits;
    } else {
        elems = bits / ElemBits + 1;
    }
    storage.clear();
    storage.resize(elems, 0);
}

bool ClassSet::getBit(int i) const { return storage[i / ElemBits] & (identity << (i % ElemBits)); }

void ClassSet::setBit(int i, bool v) {
    if (v) {
        storage[i / ElemBits] |= (identity << (i % ElemBits));
    } else {
        storage[i / ElemBits] &= ~(identity << (i % ElemBits));
    }
}

void ClassSet::insert(HashTy classHash) {
    if (cluster == nullCluster) {
        setClusterId(classes->clusterOf(classHash));
    }
    if (classes->clusterOf(classHash) != cluster) {
        throw std::runtime_error("Inserting class from a different cluster");
    }
    setBit(classes->clusterLocalIndexOf(classHash), true);
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
    for (int i = 0; i < bits; i++) {
        if (getBit(i)) {
            ++ans;
        }
    }
    return ans;
}

std::set<HashTy> ClassSet::toClasses() const {
    std::set<HashTy> answer;
    for (int i = 0; i < bits; i++) {
        if (getBit(i)) {
            answer.insert(classes->getCluster(cluster).at(i));
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
    for (int i = 0; i < elems; i++) {
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
    for (int i = 0; i < elems; i++) {
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
    for (int i = 0; i < elems; i++) {
        if ((storage[i] | rhs.storage[i]) != rhs.storage[i]) {
            return false;
        }
    }
    return true;
}