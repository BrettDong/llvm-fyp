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

#include "Utils.h"

bool beginsWith(const std::string &str, const std::string &prefix) {
    if (str.length() < prefix.length()) return false;
    return (str.compare(0, prefix.length(), prefix)) == 0;
}

std::string removePrefix(const std::string &str, const std::string &prefix) {
    if (str.compare(0, prefix.length(), prefix) != 0) {
        return str;
    }
    return str.substr(prefix.length());
}

std::string getInstSeqNum(const llvm::Value *v) {
    std::string s;
    llvm::raw_string_ostream oss(s);
    v->print(oss);
    auto p1 = s.find('%');
    auto p2 = s.find('=');
    if (p1 != std::string::npos && p2 != std::string::npos && p1 < p2) {
        return s.substr(p1, p2 - p1 - 1);
    }
    return s;
}
