#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <list>
#include "EInterface.h"

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




ExecutableFile* readFile(std::string);
ExecutableFile* readElf32(std::string);
ExecutableFile* readElf64(std::string);
ExecutableFile* readExe64(std::string);
ExecutableFile* readExe32(std::string);
