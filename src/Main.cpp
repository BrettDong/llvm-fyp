#include "Analyzer.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        llvm::errs() << "Usage: Analyzer <directory or file path>" << '\n';
        return 1;
    }

    vector<string> bitcodeFiles;

    if (filesystem::is_directory(argv[1])) {
        for (const auto &it : filesystem::recursive_directory_iterator(argv[1])) {
            if (it.path().extension() == ".bc" || it.path().extension() == ".o") {
                bitcodeFiles.push_back(it.path());
            }
        }
    } else if (filesystem::is_regular_file(argv[1])) {
        auto ext = filesystem::path(argv[1]).extension();
        if (ext == ".bc" || ext == ".o") {
            bitcodeFiles.emplace_back(argv[1]);
        } else if (ext == ".txt") {
            ifstream fin(argv[1]);
            string entry;
            while (getline(fin, entry)) {
                if (filesystem::is_regular_file(entry) &&
                    filesystem::path(entry).extension() == ".bc") {
                    bitcodeFiles.emplace_back(entry);
                }
            }
        }
    }

    std::sort(bitcodeFiles.begin(), bitcodeFiles.end());
    Analyzer analyzer;
    analyzer.analyze(bitcodeFiles);
    return 0;
}
