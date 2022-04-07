#pragma once
#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include "Common.hpp"
#include "VTable.h"

class ClassInfo {
   private:
    std::unique_ptr<VTable> vtable;
    std::set<std::string> parentClasses;
    std::string className;

   public:
    explicit ClassInfo(const std::string &className) : className(className) {}

    void decodeVTable(const Constant *initializer);
    void decodeRTTI(const Constant *initializer);

    [[nodiscard]] VTable *getVTable() const;
    [[nodiscard]] const std::set<std::string> &getParentClasses() const;
};

#endif  // CLASS_INFO_H