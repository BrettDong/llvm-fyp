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

#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "Common.hpp"

bool beginsWith(const std::string &str, const std::string &prefix);
std::string removePrefix(const std::string &str, const std::string &prefix);

template <typename T>
std::string list_out(const T &collection, std::string delim = " ") {
    std::string answer;
    for (const auto &elem : collection) {
        answer += elem;
        answer += delim;
    }
    if (!answer.empty()) {
        answer.erase(answer.end() - delim.length(), answer.end());
    }
    return answer;
}

#endif  // UTILS_H
