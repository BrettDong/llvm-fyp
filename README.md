# Course work of COMP4801 Final Year Project

![GitHub Actions](https://github.com/BrettDong/llvm-fyp/actions/workflows/build.yml/badge.svg)
![License: Apache 2.0](https://img.shields.io/badge/License-Apache%202.0-blue)

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

Examples:

```
./build/Analyzer ./sample-programs/class-hierarchy/foo.bc
./build/Analyzer ./sample-programs/class-hierarchy/
./build/Analyzer ./list.txt
```

## Compiling C++ programs to LLVM IR

Because this static analysis tool relies on RTTI in global variable section in LLVM IR modules to reconstruct class inheritance relationships, **RTTI has to be enabled** when compiling test programs. This is important to be aware of when compiling C++ projects that turn off RTTI by default, such as Chromium.

This static analysis tool recognizes virtual call sites by the following LLVM IR instructions pattern:

```llvm
  %20 = getelementptr inbounds double (%class.Shape*, double)*, double (%class.Shape*, double)** %19, i64 2
  %21 = load double (%class.Shape*, double)*, double (%class.Shape*, double)** %20, align 8
  %22 = call double %21(%class.Shape* nonnull align 8 dereferenceable(8) %17, double 1.000000e+00)
```

Compiler optimizations may alter such LLVM IR instructions pattern, so it is recommended to compile test programs with **optimization disabled** (`-O0`).

One can instruct `clang++` compiler to output LLVM IR bitcode instead of binary object files by adding `-emit-llvm` compiler argument to `CXXFLAGS`. But in general, appending `-emit-llvm` to `CXXFLAGS` will mislead build systems (e.g. `./configure`, CMake) into believing that the host compiler is unable to properly compile a C/C++ program. An alternative method to compile C++ programs to LLVM IR is to enable LTO. This is less intrusive to build systems.

As an example, for a CMake C++ project, one can compile it to LLVM IR with the following commands:

```
cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_CXX_FLAGS=-flto
cmake --build build -j 4
```

And analyze the C++ program with
```
Analyzer ./build/
```
