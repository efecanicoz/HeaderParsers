#include <vector>
#include <string>
#include <utility>

#include "EInterface.h"
#include "fileReader.h"
#include "instruction.h"

int main(int argc, char **argv)
{
	std::vector<std::pair<uint64_t, std::string>> disas = std::vector<std::pair<uint64_t, std::string>>();
	std::vector<std::string> sections;
	std::vector<uint8_t> text;
	ExecutableFile *tempDesc;
	uint32_t i;

	if(argc == 1)
		return -1;

	tempDesc = readFile(argv[1]);
	tempDesc->disassemble(disas);
	for(i = 0; i < disas.size(); i++)
	{
		printf("%x\t: %s\n",disas[i].first,disas[i].second.c_str());
	}


	delete tempDesc;
	//tempDesc
	return 0;
}
