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

#include "ClassHierarchy.h"
#include "doctest.h"

TEST_CASE("ClassHierarchyTest") {
    auto symbols = std::make_unique<ClassSymbolManager<ClassSymbol>>();
    ClassHierarchy hierarchy(symbols.get());
    CHECK(hierarchy.classCount() == 0);
    CHECK(hierarchy.clusterCount() == 0);

    auto hashA = symbols->hashClassName("A");
    auto hashB = symbols->hashClassName("B");
    auto hashC = symbols->hashClassName("C");
    auto hashD = symbols->hashClassName("D");
    auto hashE = symbols->hashClassName("E");
    auto hashX = symbols->hashClassName("X");
    auto hashY = symbols->hashClassName("Y");

    hierarchy.addRelation(hashA, hashC);
    hierarchy.addRelation(hashB, hashC);
    hierarchy.addRelation(hashB, hashD);
    hierarchy.addRelation(hashD, hashE);
    hierarchy.addRelation(hashX, hashY);

    hierarchy.clusterClasses();

    CHECK(hierarchy.classCount() == 7);
    CHECK(hierarchy.clusterCount() == 2);
    CHECK(hierarchy.getClusterOf(hashA) == hierarchy.getClusterOf(hashE));
    CHECK(hierarchy.getClusterOf(hashX) == hierarchy.getClusterOf(hashY));
    CHECK(hierarchy.getClusterOf(hashC) != hierarchy.getClusterOf(hashY));

    CHECK(hierarchy.query(hashA).toClasses() == std::set<ClassSymbol>{hashA, hashC});
    CHECK(hierarchy.query(hashB).toClasses() == std::set<ClassSymbol>{hashB, hashC, hashD, hashE});
    CHECK(hierarchy.query(hashC).toClasses() == std::set<ClassSymbol>{hashC});
    CHECK(hierarchy.query(hashD).toClasses() == std::set<ClassSymbol>{hashD, hashE});
    CHECK(hierarchy.query(hashE).toClasses() == std::set<ClassSymbol>{hashE});
    CHECK(hierarchy.query(hashX).toClasses() == std::set<ClassSymbol>{hashX, hashY});
    CHECK(hierarchy.query(hashY).toClasses() == std::set<ClassSymbol>{hashY});
}
