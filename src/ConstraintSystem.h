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

#include "ClassSet.h"
#include "Common.hpp"
#include "Symbols.h"

enum class ConstraintRelation : int { Subset, Superset };

class ConstraintSystem {
   private:
    using NodeID = int;

    friend class ConstraintSolver;

    struct Constraint {
        NodeID a;
        NodeID b;
        ConstraintRelation c;

        Constraint(NodeID a, NodeID b, ConstraintRelation c) : a(a), b(b), c(c) {}

        bool operator<(const Constraint &rhs) const;
    };

    std::set<Constraint> constraints;
    std::unordered_map<NodeID, ClassSet> constants;
    NodeID nextConstantId = -1;  // constant nodes are assigned with ID -1, -2, -3, ...
    std::set<NodeID> nodes;

    std::unordered_map<NodeID, std::set<NodeID>> forwardEdges;   // A -> B where A is subset of B
    std::unordered_map<NodeID, std::set<NodeID>> backwardEdges;  // A <- B where A is a subset of B

    std::unordered_map<NodeID, bool> backwardVisited;
    std::unordered_map<NodeID, bool> forwardVisited;

    std::string visualizeConstraintOperand(NodeID id);

   public:
    void addConstraint(NodeID a, NodeID b, ConstraintRelation c = ConstraintRelation::Subset);

    void addLiteralConstraint(NodeID a, const ClassSet &literal,
                              ConstraintRelation c = ConstraintRelation::Subset);

    void buildGraph();

    void printConstraint(Constraint constraint);

    void printConstraints();
};

#endif  // CONSTRAINT_SYSTEM_H
