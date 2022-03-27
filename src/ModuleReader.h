#pragma once
#ifndef LLVM_FYP_MODULEREADER_H
#define LLVM_FYP_MODULEREADER_H

#include "Common.hpp"

class ModuleReader {
   private:
    set<string> classNames;
    map<string, set<string>> classMethods;
    map<string, set<string>> classParents;

    void addClassMethod(const std::string &className, const std::string &functionName);
    void addClassParent(const std::string &className, const std::string &parentClassName);

    void decodeVTable(const std::string &className, const Constant *initializer);
    void decodeRTTI(const std::string &className, const Constant *initializer);

   public:
    void analyzeModule(Module *m);
    void dump();
};

#endif  // LLVM_FYP_MODULEREADER_H
