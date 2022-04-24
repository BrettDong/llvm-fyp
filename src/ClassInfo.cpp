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

#include "ClassInfo.h"

#include "Utils.h"

using namespace llvm;

void ClassInfo::decodeRTTI(const Constant *initializer) {}

std::string ClassInfo::dumpVTable() const {
    std::ostringstream oss;
    for (const auto &entry : vTable) {
        oss << '"' << demangle(entry) << '"' << ", ";
    }
    std::string str = oss.str();
    if (str.size() > 2) {
        str.erase(str.end() - 2, str.end());
    }
    return str;
}
