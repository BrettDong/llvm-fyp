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

#include "ClassAnalyzer.h"
#include "Common.hpp"
#include "ConstraintSystem.h"

class ConstraintSolver {
   private:
    using NodeTy = ConstraintSystem::NodeTy;
    using NodeID = ConstraintSystem::NodeID;
    using Elem = ConstraintSystem::Elem;

    ConstraintSystem *system;
    ClassAnalyzer *classes;
    std::map<NodeID, std::set<Elem>> answers;

    bool isSameCluster(std::set<Elem> a, std::set<Elem> b) const;

    bool intersectWith(std::set<Elem> &dst, const std::set<Elem> &src);

    bool unionWith(std::set<Elem> &dst, const std::set<Elem> &src);

   public:
    explicit ConstraintSolver(ConstraintSystem *system, ClassAnalyzer *classes)
        : system(system), classes(classes) {}
    void solve();
    bool sanityCheck();
    std::set<Elem> query(NodeTy v);
};

#endif  // CONSTRAINT_SOLVER_H
