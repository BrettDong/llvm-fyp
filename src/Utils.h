#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "Common.hpp"

bool beginsWith(const std::string &str, const std::string &prefix);
std::string removePrefix(const std::string &str, const std::string &prefix);
std::string stripTrailing(std::string className);
std::string stripClassName(std::string name);
std::string getInstSeqNum(const llvm::Value *v);

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
