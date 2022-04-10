#pragma once
#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include "Common.hpp"

class ClassInfo {
   private:
    std::vector<std::string> vTable;
    std::set<std::string> parentClasses;
    std::string className;

   public:
    explicit ClassInfo(const std::string &className) : className(className) {}

    void decodeVTable(const Constant *initializer);
    void decodeRTTI(const Constant *initializer);

    [[nodiscard]] const std::vector<std::string> &getVTable() const { return vTable; }
    [[nodiscard]] const std::set<std::string> &getParentClasses() const { return parentClasses; }
};

#endif  // CLASS_INFO_H