set(SOURCE
        Common.h
        Main.h
        Main.cpp
        )

add_executable(Analyzer ${SOURCE})
target_compile_options(Analyzer PRIVATE -fno-rtti)
target_compile_options(Analyzer PRIVATE -fPIC)
target_compile_options(Analyzer PRIVATE -Werror)
set_target_properties(Analyzer PROPERTIES CXX_STANDARD 17)
set_target_properties(Analyzer PROPERTIES CXX_STANDARD_REQUIRED ON)

target_link_libraries(Analyzer
        LLVMAsmParser
        LLVMSupport
        LLVMCore
        LLVMAnalysis
        LLVMIRReader
        LLVMBitWriter
        )
