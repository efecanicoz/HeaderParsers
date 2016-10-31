#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <list>

/*#ifndef INSTRUCTION_H
	#include "instruction.h"
#endif*/
#ifndef READER
    #include "reader.h"
#endif
#ifndef ELF64
    #include "elf64.h"
#endif
#ifndef ELF32
    #include "elf32.h"
#endif
#ifndef EXE32
	#include "exe32.h"
#endif
#ifndef EXE64
	#include "exe64.h"
#endif

class Executable
{
	virtual void init();
	virtual void readSectionTable();
	virtual std::vector<uint8_t> getSectionContent(std::string);
	virtual std::vector<std::string> getSectionNames();
};


void readFile(std::string);
Elf32 readElf32(std::string);
Elf64 readElf64(std::string);
void readExe64(std::string);
void readExe32(std::string);
