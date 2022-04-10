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

std::string stripTrailing(std::string className) {
    while (className.rfind('.') != string::npos) {
        auto dot = className.rfind('.');
        if (!std::all_of(className.begin() + dot + 1, className.end(),
                         [](char ch) { return '0' <= ch && ch <= '9'; })) {
            break;
        }
        className = className.substr(0, dot);
    }
    return className;
}

std::string stripClassName(std::string name) {
    if (beginsWith(name, "class.")) {
        name = name.substr(6);
    } else if (beginsWith(name, "struct.")) {
        name = name.substr(7);
    } else if (beginsWith(name, "union.")) {
        name = name.substr(6);
    }
    size_t dot = name.find_last_of('.');
    if (dot != std::string::npos && dot + 1 < name.length()) {
        if (std::all_of(name.begin() + dot + 1, name.end(),
                        [](const char ch) { return isdigit(ch); })) {
            name = name.substr(0, dot);
        }
    }
    return name;
}
