#!/usr/bin/env sh
set -e
LLVM_ROOT_DIR="/opt/homebrew/opt/llvm/"
LLVM_CMAKE_DIR="${LLVM_ROOT_DIR}/lib/cmake/llvm"
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release -D LLVM_DIR=${LLVM_CMAKE_DIR}
cmake --build build