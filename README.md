# Course work of COMP4801 Final Year Project

![GitHub Actions](https://github.com/BrettDong/llvm-fyp/actions/workflows/build.yml/badge.svg)

## Introduction

This is a LLVM-based static analysis tool that resolves virtual call targets in C++ programs.

It reconstructs class virtual tables and inheritance hierarchy information from LLVM IR, then performs intra-function object flow analysis to refine the set of possible dynamic types of polymorphic class objects.

## Building

### Prerequisite

#### Compiler

This program requires a C++17 compiler to compile. GCC 7 or later, or Clang 5 or later, should be enough.

#### CMake

A modern version of CMake is required. `3.16` is known to work.

| System | Command                  |
|---|--------------------------|
| Ubuntu Linux | `sudo apt install cmake` |
| macOS | `brew install cmake`     |

#### LLVM

LLVM is required.

| System | Command                    |
|---|----------------------------|
| Ubuntu Linux | `sudo apt install llvm-12` |
| macOS | `brew install llvm`        |

### Configuration

Use `LLVM_ROOT` CMake option to specify LLVM location.

* On Ubuntu, LLVM installed from APT package manager is usually in `/usr/lib/llvm-12`.
* On macOS, LLVM installed from Homebrew package manager is usually in `/opt/homebrew/opt/llvm`.

In project root directory, run the following command to configure the CMake project in `build/` subdirectory:
```
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release -D LLVM_DIR=/usr/lib/llvm-12
```

### Build

Still in project root directory, run the following command to compile:
```
cmake --build build -j 4
```

## Running

The argument can be one of
* Path to a single LLVM IR bitcode file (ending in `.bc` or `.o`)
* Path of a folder, in this case the program will search recursively for any file ending in `.bc` or `.o` and try to load them as LLVM IR bitcode modules
* Path to a `.txt` file, whose content is a list of LLVM IR bitcode file paths, one in each line


```
./build/Analyzer ./sample-programs/class-hierarchy/foo.bc
./build/Analyzer ./sample-programs/class-hierarchy/
./build/Analyzer ./list.txt
```
