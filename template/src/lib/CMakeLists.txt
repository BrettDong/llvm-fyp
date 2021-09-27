set (DragonSourceCodes
	Project.h
	Dragon.h
	Dragon.cpp
)

include_directories(${JsonHeader})

# Build executable
set (EXECUTABLE_OUTPUT_PATH ${Dragon_BINARY_DIR})
link_directories (${Dragon_BINARY_DIR}/lib)
add_executable(Dragon ${DragonSourceCodes})
target_link_libraries(Dragon
  LLVMAsmParser 
  LLVMSupport 
  LLVMCore 
  LLVMAnalysis
  LLVMIRReader
  LLVMBitWriter
  )
