#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "Common.hpp"

bool beginsWith(const std::string &str, const std::string &prefix);
std::string removePrefix(const std::string &str, const std::string &prefix);
std::string stripTrailing(std::string className);
std::string stripClassName(std::string name);

template <typename T>
std::string list_out(const T &collection) {
    std::string answer;
    for (const auto &elem : collection) {
        answer += elem;
        answer += ' ';
    }
    return answer;
}

#endif  // UTILS_H
