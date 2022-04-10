#pragma once
#ifndef CONSTRAINT_SOLVER_H
#define CONSTRAINT_SOLVER_H

#include "Common.hpp"

enum class SetConstraintType : int { Subset, Superset };

class SetConstraintSolver {
   private:
    using NodeTy = const Value *;
    using NodeID = int;
    using Elem = string;

    struct SetConstraint {
        NodeID a;
        NodeID b;
        SetConstraintType c;

        SetConstraint(NodeID a, NodeID b, SetConstraintType c) : a(a), b(b), c(c) {}
    };

    map<NodeID, set<Elem>> answers;
    vector<SetConstraint> constraints;
    set<NodeID> constants;
    set<NodeID> nodes;
    map<NodeTy, NodeID> idMap;
    NodeID nextId = 0;

    map<NodeID, set<NodeID>> forwardEdges;   // A -> B where A is subset of B
    map<NodeID, set<NodeID>> backwardEdges;  // A <- B where A is a subset of B

    map<NodeID, bool> backwardVisited;
    map<NodeID, bool> forwardVisited;

    bool intersectWith(set<Elem> &dst, const set<Elem> &src);

    bool unionWith(set<Elem> &dst, const set<Elem> &src);

   public:
    void addConstraint(NodeTy a, NodeTy b, SetConstraintType c = SetConstraintType::Subset);

    void addLiteralConstraint(NodeTy a, const set<Elem> &literal,
                              SetConstraintType c = SetConstraintType::Subset);

    void buildGraph();

    void solve();

    set<Elem> query(NodeTy v);
};

#endif  // CONSTRAINT_SOLVER_H
