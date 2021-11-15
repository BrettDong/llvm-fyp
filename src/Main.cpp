#include <filesystem>

#include "Common.hpp"
#include "mlta/CallGraph.h"

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

int main(int argc, char **argv) {
    cl::ParseCommandLineOptions(argc, argv, "Analyzer\n");
    if (!filesystem::is_directory(BitcodeFilesDir.getValue())) {
        errs() << "\"" << BitcodeFilesDir << "\" is not a directory.\n";
        return 1;
    }

    unique_ptr<LLVMContext> llvmContext = make_unique<LLVMContext>();
    SMDiagnostic err;

    GlobalContext globalCtx;
    globalCtx.csvout.open("analyzer.csv", ios::trunc);

    vector<string> bitcodeFiles;

    for (const auto &it : filesystem::recursive_directory_iterator(BitcodeFilesDir.getValue())) {
        if (it.path().extension() == ".bc") {
            bitcodeFiles.push_back(it.path());
            outs() << "Reading bitcode file: " << it.path() << "\n";
            unique_ptr<Module> module = parseIRFile(it.path().string(), err, *llvmContext);
            if (!module) {
                errs() << "Error loading bitcode file \"" << it.path() << "\": " << err.getMessage()
                       << "\n";
                continue;
            }
            Module *m = module.release();
            string name = it.path().filename().string();
            globalCtx.Modules.emplace_back(m, name);
        }
    }

    CallGraphPass CGPass(&globalCtx);
    CGPass.run(globalCtx.Modules);

    for (const string &bitcodeFile : bitcodeFiles) {
        CGPass.resolveVirtualCallTargets(bitcodeFile);
    }

    //    for (const auto &callee : globalCtx.Callers) {
    //        outs() << "Callee: " << demangle(callee.first->getName().str()) << " has "
    //               << callee.second.size() << " callers identified \n";
    //        for (const auto caller : callee.second) {
    //            outs() << "    called from " << demangle(caller->getFunction()->getName().str());
    //            if (find(globalCtx.IndirectCallInsts.begin(), globalCtx.IndirectCallInsts.end(),
    //                     caller) != globalCtx.IndirectCallInsts.end()) {
    //                outs() << " <= is an indirect call";
    //            }
    //            outs() << '\n';
    //        }
    //    }
    return 0;
}
