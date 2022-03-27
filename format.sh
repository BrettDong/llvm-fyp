#!/bin/sh
find src -iname "*.cpp" -o -iname "*.h" | xargs clang-format --style=file -i

