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

ClassSet::ClassSet(ClassAnalyzer *classes, int cluster) : classes(classes), cluster(cluster) {
    bits = static_cast<int>(classes->getCluster(cluster).size());
    storage.reserve(bits / ElemBits + 1);
    for (int i = 0; i < bits / ElemBits + 1; i++) {
        storage[i] = 0;
    }
}

bool ClassSet::getBit(int i) const { return storage[i / ElemBits] & (identity << (i % ElemBits)); }

void ClassSet::setBit(int i, bool v) {
    if (v) {
        storage[i / ElemBits] |= (identity << (i % ElemBits));
    } else {
        storage[i / ElemBits] &= ~(identity << (i % ElemBits));
    }
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
