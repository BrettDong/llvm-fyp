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
#ifndef CONSTRAINT_SOLVER_H
#define CONSTRAINT_SOLVER_H

#include "ClassHierarchy.h"
#include "Common.hpp"
#include "ConstraintSystem.h"

class ConstraintSolver {
   private:
    using NodeID = ConstraintSystem::NodeID;

    ConstraintSystem *system;
    ClassHierarchy *hierarchy;
    std::map<NodeID, ClassSet> answers;

    bool intersectWith(ClassSet &dst, const ClassSet &src);

    bool unionWith(ClassSet &dst, const ClassSet &src);

   public:
    explicit ConstraintSolver(ConstraintSystem *system, ClassHierarchy *hierarchy)
        : system(system), hierarchy(hierarchy) {}
    void solve();
    bool sanityCheck();
    ClassSet query(NodeID v) const;
};

#endif  // CONSTRAINT_SOLVER_H
