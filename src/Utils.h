#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "Common.hpp"

bool beginsWith(const std::string &str, const std::string &prefix);
std::string removePrefix(const std::string &str, const std::string &prefix);
std::string stripTrailing(std::string className);

#endif  // UTILS_H
