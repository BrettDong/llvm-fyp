# llvm-fyp

## Building

`LLVM_DIR` points to the location of CMake configuration files in LLVM. For example, on Ubuntu Linux, it might be `/usr/lib/llvm-12/cmake`; on macOS, if LLVM is installed from Homebrew, `LLVM_DIR` is `/opt/homebrew/opt/llvm/lib/cmake/llvm`.

```
cmake -S . -B build -D LLVM_DIR=/usr/lib/llvm-12/cmake
cmake --build build
```

## Running

The first argument is the folder that contains LLVM bitcode files.

```
./build/src/Analyzer ./sample-programs/class-hierarchy
```