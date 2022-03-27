#include <filesystem>

#include "Common.hpp"
#include "ModuleReader.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        errs() << "Usage: Analyzer <directory or file path>" << '\n';
        return 1;
    }

    vector<string> bitcodeFiles;

    if (filesystem::is_directory(argv[1])) {
        for (const auto &it : filesystem::recursive_directory_iterator(argv[1])) {
            if (it.path().extension() == ".bc") {
                bitcodeFiles.push_back(it.path());
            }
        }
    } else if (filesystem::is_regular_file(argv[1])) {
        bitcodeFiles.emplace_back(argv[1]);
    }

    unique_ptr<LLVMContext> llvmContext = make_unique<LLVMContext>();
    SMDiagnostic err;

    std::sort(bitcodeFiles.begin(), bitcodeFiles.end());
    map<string, int> types;

    for (const string &it : bitcodeFiles) {
        outs() << "Reading bitcode file: " << it << "\n";
        unique_ptr<Module> module = parseIRFile(it, err, *llvmContext);
        if (!module) {
            errs() << "Error loading bitcode file \"" << it << "\": " << err.getMessage() << "\n";
            continue;
        }
        ModuleReader reader;
        reader.analyzeModule(module.get());
        reader.dump();
    }

    return 0;
}
