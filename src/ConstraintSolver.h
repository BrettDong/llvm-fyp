#pragma once
#ifndef CONSTRAINT_SOLVER_H
#define CONSTRAINT_SOLVER_H

#include "Common.hpp"
#include "ConstraintSystem.h"

class ConstraintSolver {
   protected:
    using NodeTy = ConstraintSystem::NodeTy;
    using NodeID = ConstraintSystem::NodeID;
    using Elem = ConstraintSystem::Elem;

   public:
    ConstraintSolver() = delete;
    explicit ConstraintSolver(const ConstraintSystem *system) {}
    virtual ~ConstraintSolver() = default;
    virtual void solve() = 0;
    virtual bool sanityCheck() = 0;
    virtual set<Elem> query(NodeTy v) = 0;
};

class ConstraintSolverV1 : public ConstraintSolver {
   protected:
    ConstraintSystem *system;
    map<NodeID, set<Elem>> answers;

    bool intersectWith(set<Elem> &dst, const set<Elem> &src);

    bool unionWith(set<Elem> &dst, const set<Elem> &src);

   public:
    explicit ConstraintSolverV1(ConstraintSystem *system)
        : ConstraintSolver(system), system(system) {}
    void solve() override;
    bool sanityCheck() override;
    set<Elem> query(NodeTy v) override;
};

class ConstraintSolverV2 : public ConstraintSolverV1 {
   public:
    explicit ConstraintSolverV2(ConstraintSystem *system) : ConstraintSolverV1(system) {}
    void solve() override;
};

#endif  // CONSTRAINT_SOLVER_H
