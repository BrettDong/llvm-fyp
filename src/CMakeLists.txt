set(SOURCE
        Common.hpp
        Main.cpp
        mlta/Analyzer.h
        mlta/Analyzer.cpp
        mlta/Common.h
        mlta/Common.cpp
        mlta/CallGraph.h
        mlta/CallGraph.cpp
        mlta/VirtualCallTargets.h
        mlta/VirtualCallTargets.cpp
        )

add_executable(Analyzer ${SOURCE})
target_compile_options(Analyzer PRIVATE -fno-rtti)
target_compile_options(Analyzer PRIVATE -fPIC)
target_compile_options(Analyzer PRIVATE -Werror)
if (SANITIZERS)
    target_compile_options(Analyzer PRIVATE -fsanitize=address,undefined)
    target_link_options(Analyzer PRIVATE -fsanitize=address,undefined)
endif ()
set_target_properties(Analyzer PROPERTIES CXX_STANDARD 17)
set_target_properties(Analyzer PROPERTIES CXX_STANDARD_REQUIRED ON)
target_precompile_headers(Analyzer PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/Common.hpp>")

target_link_libraries(Analyzer
        LLVMAnalysis
        LLVMAsmParser
        LLVMBitWriter
        LLVMCore
        LLVMIRReader
        LLVMPasses
        LLVMSupport
        )
