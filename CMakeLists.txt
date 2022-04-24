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
        src/ClassInfo.cpp
        src/ClassSet.cpp
        src/Common.hpp
        src/ConstraintSolver.cpp
        src/ConstraintSystem.cpp
        src/FunctionObjectFlow.cpp
        src/Symbols.cpp
        src/Utils.cpp
        )

set(TEST_SOURCE
        tests/ClassSymbolTest.cpp
        tests/TestMain.cpp
        )

add_library(Common INTERFACE)
target_include_directories(Common INTERFACE src)
target_compile_options(Common INTERFACE -fno-rtti)
target_compile_options(Common INTERFACE -fPIC)
target_compile_options(Common INTERFACE -Werror)
if (SANITIZERS)
    target_compile_options(Common INTERFACE -fsanitize=address,undefined)
    target_link_options(Common INTERFACE -fsanitize=address,undefined)
endif ()
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if (COMPILER_SUPPORTS_MARCH_NATIVE)
    target_compile_options(Common INTERFACE -march=native)
endif ()
target_precompile_headers(Common INTERFACE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/Common.hpp>")

target_link_libraries(Common INTERFACE
        LLVMAnalysis
        LLVMAsmParser
        LLVMBitWriter
        LLVMCore
        LLVMIRReader
        LLVMPasses
        LLVMSupport
        )

add_library(AnalyzerCommon STATIC ${SOURCE})
target_link_libraries(AnalyzerCommon Common)
set_target_properties(AnalyzerCommon PROPERTIES CXX_STANDARD 17)
set_target_properties(AnalyzerCommon PROPERTIES CXX_STANDARD_REQUIRED ON)

add_executable(Analyzer src/Main.cpp)
target_link_libraries(Analyzer AnalyzerCommon)
set_target_properties(Analyzer PROPERTIES CXX_STANDARD 17)
set_target_properties(Analyzer PROPERTIES CXX_STANDARD_REQUIRED ON)

add_executable(AnalyzerTest ${TEST_SOURCE})
target_link_libraries(AnalyzerTest AnalyzerCommon)
set_target_properties(AnalyzerTest PROPERTIES CXX_STANDARD 17)
set_target_properties(AnalyzerTest PROPERTIES CXX_STANDARD_REQUIRED ON)
target_precompile_headers(AnalyzerTest PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/tests/doctest.h>")
set_source_files_properties(tests/TestMain.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
enable_testing()
add_test(NAME AnalyzerTest COMMAND $<TARGET_FILE:AnalyzerTest>)
