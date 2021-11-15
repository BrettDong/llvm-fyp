#include <filesystem>

#include "Common.hpp"

static cl::opt<std::string> BitcodeFilesDir(
    cl::Positional, cl::desc("[The directory that contains bitcode files.]"), cl::Required);

void disassembleModule(Module *module) {
    ModuleSlotTracker moduleSlotTracker(module);
    for (const Function &f : module->getFunctionList()) {
        outs() << "    Function: " << demangle(f.getName().str()) << "\n";
        moduleSlotTracker.incorporateFunction(f);
        for (const BasicBlock &block : f.getBasicBlockList()) {
            for (const Instruction &inst : block.getInstList()) {
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

void analyzeModule(Module *module) {
    for (const GlobalVariable &global : module->getGlobalList()) {
        const std::string name = demangle(global.getName().str());
        outs() << "Global: " << name << " has type " << *(global.getValueType()) << "\n";
        if (global.hasInitializer()) {
            const Constant *constant = global.getInitializer();
            if (name.find("vtable for ") != std::string::npos ||
                name.find("typeinfo for ") != std::string::npos) {
                if (const ConstantAggregate *aggregate = dyn_cast<ConstantAggregate>(constant)) {
                    const unsigned int n = aggregate->getNumOperands();
                    for (unsigned int i = 0; i < n; i++) {
                        const Constant *element = aggregate->getAggregateElement(i);
                        if (const ConstantAggregate *inner = dyn_cast<ConstantAggregate>(element)) {
                            const unsigned int m = inner->getNumOperands();
                            for (unsigned int j = 0; j < m; j++) {
                                const Constant *innerElement = inner->getAggregateElement(j);
                                outs() << *(innerElement->getType()) << ", ";
                            }
                        } else if (const ConstantExpr *expr = dyn_cast<ConstantExpr>(element)) {
                            outs() << *(expr->getType()) << ", ";
                        } else if (const ConstantInt *integer = dyn_cast<ConstantInt>(element)) {
                            outs() << *(integer->getType()) << ", ";
                        }
                    }
                }
            } else if (name.find("typeinfo name for ") != std::string::npos) {
                if (const ConstantDataArray *data = dyn_cast<ConstantDataArray>(constant)) {
                    const unsigned int n = data->getNumElements();
                    for (unsigned int i = 0; i < n; i++) {
                        char ch = static_cast<char>(data->getElementAsInteger(i));
                        if (ch == '\0') break;
                        outs() << ch;
                    }
                }
            }
            outs() << "\n";
        }
    }
}

int main(int argc, char **argv) {
    cl::ParseCommandLineOptions(argc, argv, "Analyzer\n");
    if (!filesystem::is_directory(BitcodeFilesDir.getValue())) {
        errs() << "\"" << BitcodeFilesDir << "\" is not a directory.\n";
        return 1;
    }

    unique_ptr<LLVMContext> llvmContext = make_unique<LLVMContext>();
    SMDiagnostic err;

    for (const auto &it : filesystem::recursive_directory_iterator(BitcodeFilesDir.getValue())) {
        if (it.path().extension() == ".bc") {
            outs() << "Reading bitcode file: " << it.path() << "\n";
            unique_ptr<Module> module = parseIRFile(it.path().string(), err, *llvmContext);
            if (!module) {
                errs() << "Error loading bitcode file \"" << it.path() << "\": " << err.getMessage()
                       << "\n";
                continue;
            }
            analyzeModule(module.get());
        }
    }

    return 0;
}
