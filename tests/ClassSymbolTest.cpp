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

#include "Symbols.h"
#include "doctest.h"

TEST_CASE("ClassSymbolTest") {
    ClassSymbolManager<ClassSymbol> symbolManager;
    const std::string classA = "Foo";
    const std::string classB = "Bar";
    REQUIRE(classA != classB);

    CHECK(symbolManager.existClassName(classA) == false);
    CHECK(symbolManager.existClassName(classB) == false);

    auto hashA = symbolManager.hashClassName(classA);
    CHECK(symbolManager.existClassName(classA) == true);
    CHECK(symbolManager.existClassName(classB) == false);
    CHECK(symbolManager.hashClassName(classA) == hashA);
    CHECK(symbolManager.hashClassName("class." + classA) == hashA);
    CHECK(symbolManager.hashClassName("class." + classA + ".123") == hashA);
    CHECK(symbolManager.hashClassName("class." + classA + ".123.456") == hashA);

    auto hashB = symbolManager.hashClassName("class." + classB + ".123.456");
    CHECK(symbolManager.existClassName(classA) == true);
    CHECK(symbolManager.existClassName(classB) == true);
    CHECK(symbolManager.hashClassName(classA) == hashA);
    CHECK(symbolManager.hashClassName(classB) == hashB);
    CHECK(hashA != hashB);
    CHECK(symbolManager.hashClassName("class." + classA) == hashA);
    CHECK(symbolManager.hashClassName("class." + classA + ".123") == hashA);
    CHECK(symbolManager.hashClassName("class." + classA + ".123.456") == hashA);
    CHECK(symbolManager.hashClassName("class." + classB) == hashB);
    CHECK(symbolManager.hashClassName("class." + classB + ".123") == hashB);
}
