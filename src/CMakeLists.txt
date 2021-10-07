set(SOURCE
        Common.h
        Main.h
        Main.cpp
        )

add_executable(Analyzer ${SOURCE})
target_link_libraries(Analyzer
        LLVMAsmParser
        LLVMSupport
        LLVMCore
        LLVMAnalysis
        LLVMIRReader
        LLVMBitWriter
        )
