#include <filesystem>

#include "ClassAnalyzer.h"
#include "Common.hpp"

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
    map<string, unique_ptr<Module>> modules;
    ClassAnalyzer classAnalyzer;

    for (const string &file : bitcodeFiles) {
        outs() << "Reading bitcode file: " << file << "\n";
        unique_ptr<Module> module = parseIRFile(file, err, *llvmContext);
        if (!module) {
            errs() << "Error loading bitcode file \"" << file << "\": " << err.getMessage() << "\n";
            continue;
        }
        modules[file] = std::move(module);
    }

    for (const auto &[string, module] : modules) {
        classAnalyzer.analyzeModule(module.get());
    }

    ClassHierarchyGraph graph = classAnalyzer.buildClassHierarchyGraph();

    for (const std::string &className : classAnalyzer.getClasses()) {
        set<string> derivedClasses = graph.queryDerivedClasses(className);
        if (!derivedClasses.empty()) {
            outs() << "class " << className << " has " << derivedClasses.size()
                   << " derived classes.\n";
        }
    }

    return 0;
}
