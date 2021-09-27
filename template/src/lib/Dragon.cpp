#include "Dragon.h"

CodeStructure *CS;

static cl::opt<std::string> BitcodeFileDir(cl::Positional, cl::desc("[The directory that contains bitcode files.]"), cl::Required);
static cl::opt<std::string> LinkedFiles(cl::Positional, cl::desc("[The text file that contains the bitcode files linked into the binary.]"), cl::Required);
static cl::opt<std::string> OutDir(cl::Positional, cl::desc("[The out directory.]"), cl::Required);

int main(int argc, char** argv) 
{
	CS = new CodeStructure();

	cl::ParseCommandLineOptions(argc, argv, "Parsing arguments\n");
	
	// read the text file to get the bicode files linked into the binary
	unordered_set<string> linkedFiles;
	ifstream in_f (LinkedFiles.data());
	string line;
	while (std::getline(in_f, line)) {
		linkedFiles.insert(line);
	}
	in_f.close();
	
	// collect the bitcode files
	struct dirent *entry = nullptr;
	DIR *dp = nullptr;

	dp = opendir(BitcodeFileDir.data());
	if (dp == nullptr)
		assert(false);

	CodeStructure::outDir = OutDir.data();

	return 0;
}
