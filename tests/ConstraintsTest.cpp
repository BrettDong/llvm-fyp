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

#include "ConstraintSolver.h"
#include "Symbols.h"
#include "doctest.h"

TEST_CASE("ConstraintsTest") {
    auto symbols = std::make_unique<ClassSymbolManager<ClassSymbol>>();
    auto hashA = symbols->hashClassName("A");
    auto hashB = symbols->hashClassName("B");
    auto hashC = symbols->hashClassName("C");
    auto hierarchy = std::make_unique<ClassHierarchy>(symbols.get());
    hierarchy->addRelation(hashA, hashB);
    hierarchy->addRelation(hashA, hashC);
    hierarchy->clusterClasses();
    auto constraintSystem = std::make_unique<ConstraintSystem>();
    constraintSystem->addConstraint(9, 2);
    constraintSystem->addConstraint(15, 2);
    constraintSystem->addConstraint(9, 6);
    constraintSystem->addConstraint(15, 12);
    ClassSet sABC(hierarchy.get(), hierarchy->getClusterOf(hashA));
    sABC.insert(hashA);
    sABC.insert(hashB);
    sABC.insert(hashC);
    ClassSet sB(hierarchy.get(), hierarchy->getClusterOf(hashB));
    sB.insert(hashB);
    ClassSet sC(hierarchy.get(), hierarchy->getClusterOf(hashC));
    sC.insert(hashC);
    constraintSystem->addLiteralConstraint(9, sABC);
    constraintSystem->addLiteralConstraint(15, sABC);
    constraintSystem->addLiteralConstraint(6, sB);
    constraintSystem->addLiteralConstraint(12, sC);
    constraintSystem->buildGraph();
    auto constraintSolver =
        std::make_unique<ConstraintSolver>(constraintSystem.get(), hierarchy.get());
    constraintSolver->solve();
    CHECK(constraintSolver->query(2).toClasses() == std::set<ClassSymbol>{hashB, hashC});
}
