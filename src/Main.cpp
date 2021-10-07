#include <filesystem>
#include <llvm/Demangle/Demangle.h>
#include <llvm/IR/ModuleSlotTracker.h>
#include "Main.h"

static cl::opt<std::string> BitcodeFilesDir(cl::Positional,
                                            cl::desc("[The directory that contains bitcode files.]"),
                                            cl::Required);

int main(int argc, char **argv) {
    cl::ParseCommandLineOptions(argc, argv, "Analyzer\n");
    if (!filesystem::is_directory(BitcodeFilesDir.getValue())) {
        errs() << "\"" << BitcodeFilesDir << "\" is not a directory.\n";
        return 1;
    }

    unique_ptr<LLVMContext> llvmContext = make_unique<LLVMContext>();
    SMDiagnostic err;

    for (const auto &it: filesystem::recursive_directory_iterator(BitcodeFilesDir.getValue())) {
        if (it.path().extension() == ".bc") {
            outs() << "Reading bitcode file: " << it.path() << "\n";
            unique_ptr<Module> module = parseIRFile(it.path().string(), err, *llvmContext);
            if (!module) {
                errs() << "Error loading bitcode file \"" << it.path() << "\": " << err.getMessage() << "\n";
                continue;
            }
            ModuleSlotTracker moduleSlotTracker(module.get());
            for (const Function &f: module->getFunctionList()) {
                outs() << "    Function: " << demangle(f.getName().str()) << "\n";
                moduleSlotTracker.incorporateFunction(f);
                for (const BasicBlock &block: f.getBasicBlockList()) {
                    for (const Instruction &inst: block.getInstList()) {
                        outs() << "        ";
                        if (inst.hasName()) {
                            outs() << inst.getName() << " = ";
                        } else if (!inst.getType()->isVoidTy()) {
                            outs() << "%" << moduleSlotTracker.getLocalSlot(&inst) << " = ";
                        }
                        outs() << inst.getOpcodeName() << " ";
                        unsigned int numOperands = inst.getNumOperands();
                        for (unsigned int operand = 0; operand < numOperands; operand++) {
                            inst.getOperand(operand)->printAsOperand(outs());
                            if (operand < numOperands - 1) {
                                outs() << " , ";
                            }
                        }
                        outs() << '\n';
                    }
                }
            }
        }
    }

    return 0;
}
