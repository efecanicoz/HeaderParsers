#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <list>
#include "EInterface.h"

#include "reader.h"
#include "elf64.h"
#include "elf32.h"
#include "exe32.h"
#include "exe64.h"

ExecutableFile* readFile(std::string);
ExecutableFile* readElf32(std::string);
ExecutableFile* readElf64(std::string);
ExecutableFile* readExe64(std::string);
ExecutableFile* readExe32(std::string);

#endif
