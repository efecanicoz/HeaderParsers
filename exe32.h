//
//  exe32.h
//  Exe
//
//  Created by İsmail Fırat Sezel on 28/09/16.
//  Copyright © 2016 İsmail Fırat Sezel. All rights reserved.
//


#ifndef READER
#include "readerExe.h"
#endif
#ifndef EXE32

#define EXE32
#include <cstdint>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>

class Exe32
{
public:
    struct exe_ident id;
    struct exe_coff coff;
    struct exe_section_table st;
    std::vector<exe_section_table> buffer;
    
    std::ifstream fd;

    Exe32(std::ifstream&);
    Exe32(std::string);
    
    void readDosHeader();
    void readPESignature();
    void readCoffHeader();
    void readSectionTable();

};
#endif
