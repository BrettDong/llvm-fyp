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

TEST_CASE("ClassSetTest") {
    auto symbols = std::make_unique<ClassSymbolManager<ClassSymbol>>();
    ClassHierarchy hierarchy(symbols.get());
    auto hashA = symbols->hashClassName("A");
    auto hashB = symbols->hashClassName("B");
    auto hashC = symbols->hashClassName("C");
    hierarchy.addRelation(hashA, hashB);
    hierarchy.addRelation(hashB, hashC);
    hierarchy.clusterClasses();

    ClassSet s(&hierarchy, 0);
    CHECK(s.count() == 0);
    CHECK(s.toClasses().empty());

    s.insert(hashA);
    CHECK(s.count() == 1);
    CHECK(s.toClasses() == std::set<ClassSymbol>{hashA});

    s.insert(hashA);
    CHECK(s.count() == 1);
    CHECK(s.toClasses() == std::set<ClassSymbol>{hashA});

    ClassSet t(&hierarchy);
    CHECK(t.count() == 0);
    CHECK(t.toClasses().empty());

    CHECK(t.isSubSetOf(s) == true);
    CHECK(s.isSubSetOf(t) == false);

    CHECK(t.unionWith(s) == true);
    CHECK(t.count() == 1);
    CHECK(t.toClasses() == std::set<ClassSymbol>{hashA});
    CHECK(t.isSubSetOf(s) == true);
    CHECK(s.isSubSetOf(t) == true);

    s.insert(hashB);
    CHECK(s.count() == 2);
    CHECK(s.toClasses() == std::set<ClassSymbol>{hashA, hashB});
    CHECK(t.isSubSetOf(s) == true);
    CHECK(s.isSubSetOf(t) == false);

    CHECK(t.intersectWith(s) == false);
    CHECK(t.count() == 1);
    CHECK(t.toClasses() == std::set<ClassSymbol>{hashA});

    CHECK(t.unionWith(s) == true);
    CHECK(t.count() == 2);
    CHECK(t.toClasses() == std::set<ClassSymbol>{hashA, hashB});
}
