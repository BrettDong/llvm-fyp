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
