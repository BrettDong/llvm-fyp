cmake_minimum_required(VERSION 3.16)
project(LLVM-FYP)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(SOURCE
        src/Analyzer.cpp
        src/ClassAnalyzer.cpp
        src/ClassHierarchyGraph.cpp
        src/ClassInfo.cpp
        src/Common.hpp
        src/ConstraintSolver.cpp
        src/ConstraintSystem.cpp
        src/FunctionObjectFlow.cpp
        src/Main.cpp
        src/Symbols.cpp
        src/Utils.cpp
        )

add_executable(Analyzer ${SOURCE})
target_include_directories(Analyzer PRIVATE src)
target_compile_options(Analyzer PRIVATE -fno-rtti)
target_compile_options(Analyzer PRIVATE -fPIC)
target_compile_options(Analyzer PRIVATE -Werror)
if (SANITIZERS)
    target_compile_options(Analyzer PRIVATE -fsanitize=address,undefined)
    target_link_options(Analyzer PRIVATE -fsanitize=address,undefined)
endif ()
set_target_properties(Analyzer PROPERTIES CXX_STANDARD 17)
set_target_properties(Analyzer PROPERTIES CXX_STANDARD_REQUIRED ON)
target_precompile_headers(Analyzer PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/Common.hpp>")

target_link_libraries(Analyzer
        LLVMAnalysis
        LLVMAsmParser
        LLVMBitWriter
        LLVMCore
        LLVMIRReader
        LLVMPasses
        LLVMSupport
        )
