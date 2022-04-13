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
#ifndef CONSTRAINT_SYSTEM_H
#define CONSTRAINT_SYSTEM_H

#include "Common.hpp"
#include "Symbols.h"

enum class ConstraintRelation : int { Subset, Superset };

class ConstraintSystem {
   private:
    using NodeTy = const llvm::Value *;
    using NodeID = int;
    using Elem = HashTy;

    friend class ConstraintSolver;
    friend class ConstraintSolverV1;
    friend class ConstraintSolverV2;

    struct Constraint {
        NodeID a;
        NodeID b;
        ConstraintRelation c;

        Constraint(NodeID a, NodeID b, ConstraintRelation c) : a(a), b(b), c(c) {}
    };

    std::vector<Constraint> constraints;
    std::map<NodeID, std::set<Elem>> constants;
    std::set<NodeID> nodes;
    std::map<NodeTy, NodeID> idMap;
    NodeID nextId = 0;

    std::map<NodeID, std::set<NodeID>> forwardEdges;   // A -> B where A is subset of B
    std::map<NodeID, std::set<NodeID>> backwardEdges;  // A <- B where A is a subset of B

    std::map<NodeID, bool> backwardVisited;
    std::map<NodeID, bool> forwardVisited;

    std::optional<NodeTy> lookupNodeID(const NodeID &id);

    std::string visualizeConstraintOperand(const NodeID &id);

   public:
    void addConstraint(NodeTy a, NodeTy b, ConstraintRelation c = ConstraintRelation::Subset);

    void addLiteralConstraint(NodeTy a, const std::set<Elem> &literal,
                              ConstraintRelation c = ConstraintRelation::Subset);

    void buildGraph();

    void printConstraint(Constraint constraint);

    void printConstraints();
};

#endif  // CONSTRAINT_SYSTEM_H
