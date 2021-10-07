#!/bin/sh
find . -iname "*.cpp" -o -iname "*.h" | xargs clang-format --style=file -i

