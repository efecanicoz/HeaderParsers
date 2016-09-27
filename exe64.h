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



class Exe64
{
    public:
        struct exe_ident id;
        struct exe_coff  coff;
        struct exe_section_table st;
        std::ifstream fd;
/*Section eklenecek*/
        void read(uint8_t*,uint8_t*,uint8_t);
        void read(uint16_t*,uint8_t*,uint8_t);
        void read(uint32_t*,uint8_t*,uint8_t);
        void read(uint64_t*,uint8_t*,uint8_t);
        void pointTobit(int offset);
 
        Exe64(std::ifstream&);
        Exe64(std::string);
        
        void readDosHeader();
        void readPESignature();
        void readCoffHeader();
        void readSectionTable();
 /*Section eklenecek*/
};
#endif
