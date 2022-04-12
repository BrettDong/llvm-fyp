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
