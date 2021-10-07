#include "Main.h"

static cl::opt<std::string> BitcodeFileDir(cl::Positional,
                                           cl::desc("[The directory that contains bitcode files.]"),
                                           cl::Required);

int main(int argc, char **argv) {
    cl::ParseCommandLineOptions(argc, argv, "Parsing arguments\n");

    // collect the bitcode files
    struct dirent *entry = nullptr;
    DIR *dp = nullptr;

    dp = opendir(BitcodeFileDir.data());
    if (dp == nullptr) assert(false);

    return 0;
}
