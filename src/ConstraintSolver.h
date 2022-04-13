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
