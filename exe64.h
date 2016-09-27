#ifndef READER
    #include "readerExe.h"
#endif
#ifndef EXE64

#define EXE64
#include <cstdint>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>

/*Coff Header*/
class Exe64CH {
    uint32_t Machine;
    uint32_t NumberOfSections;
    uint64_t TimeDateStamp;
    uint64_t PointerToSymbolTable;
    uint64_t NumberOfSymbols;
    uint32_t SizeOfOptionalHeader;
    uint32_t Characteristics;
};

class Exe64
{
    public:
        struct exe_ident id;
        std::ifstream fd;
/*Section eklenecek*/
        void read(uint8_t*,uint8_t*,uint8_t);
        void read(uint16_t*,uint8_t*,uint8_t);
        void read(uint32_t*,uint8_t*,uint8_t);
        void read(uint64_t*,uint8_t*,uint8_t);
 
        Exe64(std::ifstream&);
        Exe64(std::string);
        
        void readDosHeader();
 /*Section eklenecek*/      
};
#endif
