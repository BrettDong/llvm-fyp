#include "Analyzer.h"

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

    std::sort(bitcodeFiles.begin(), bitcodeFiles.end());
    Analyzer analyzer;
    analyzer.analyze(bitcodeFiles);
    return 0;
}
