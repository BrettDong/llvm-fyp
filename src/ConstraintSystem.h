#pragma once
#ifndef CONSTRAINT_SYSTEM_H
#define CONSTRAINT_SYSTEM_H

#include "Common.hpp"

enum class ConstraintRelation : int { Subset, Superset };

class ConstraintSystem {
   private:
    using NodeTy = const Value *;
    using NodeID = int;
    using Elem = string;

    friend class ConstraintSolver;
    friend class ConstraintSolverV1;

    struct Constraint {
        NodeID a;
        NodeID b;
        ConstraintRelation c;

        Constraint(NodeID a, NodeID b, ConstraintRelation c) : a(a), b(b), c(c) {}
    };

    vector<Constraint> constraints;
    map<NodeID, set<Elem>> constants;
    set<NodeID> nodes;
    map<NodeTy, NodeID> idMap;
    NodeID nextId = 0;

    map<NodeID, set<NodeID>> forwardEdges;   // A -> B where A is subset of B
    map<NodeID, set<NodeID>> backwardEdges;  // A <- B where A is a subset of B

    map<NodeID, bool> backwardVisited;
    map<NodeID, bool> forwardVisited;

    optional<NodeTy> lookupNodeID(const NodeID &id);

    string visualizeConstraintOperand(const NodeID &id);

   public:
    void addConstraint(NodeTy a, NodeTy b, ConstraintRelation c = ConstraintRelation::Subset);

    void addLiteralConstraint(NodeTy a, const set<Elem> &literal,
                              ConstraintRelation c = ConstraintRelation::Subset);

    void buildGraph();

    void printConstraint(Constraint constraint);

    void printConstraints();
};

#endif  // CONSTRAINT_SYSTEM_H
