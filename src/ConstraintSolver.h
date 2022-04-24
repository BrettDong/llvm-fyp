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
    using NodeTy = ConstraintSystem::NodeTy;
    using NodeID = ConstraintSystem::NodeID;
    using Elem = ConstraintSystem::Elem;

    ConstraintSystem *system;
    ClassHierarchy *hierarchy;
    std::map<NodeID, ClassSet> answers;

    bool isSameCluster(std::set<Elem> a, std::set<Elem> b) const;

    bool intersectWith(ClassSet &dst, const ClassSet &src);

    bool unionWith(ClassSet &dst, const ClassSet &src);

   public:
    explicit ConstraintSolver(ConstraintSystem *system, ClassHierarchy *hierarchy)
        : system(system), hierarchy(hierarchy) {}
    void solve();
    bool sanityCheck();
    ClassSet query(NodeTy v);
};

#endif  // CONSTRAINT_SOLVER_H
