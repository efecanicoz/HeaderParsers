#ifndef READER
#define READER

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <list>


struct exe_ident {
	uint8_t exe_magic[2];
	uint8_t exe_bytes_in_last_block;
  	uint8_t exe_blocks_in_file;
  	uint8_t exe_num_relocs;
  	uint8_t exe_header_paragraphs;
  	uint8_t exe_min_extra_paragraphs;
  	uint8_t exe_max_extra_paragraphs;
  	uint8_t exe_ss;
  	uint8_t exe_sp;
  	uint8_t exe_checksum;
  	uint8_t exe_ip;
  	uint8_t exe_cs;
	uint8_t exe_relocpos;
     	uint8_t exe_noverlay;
     	uint8_t exe_reserved1[4];
     	uint8_t exe_oem_id;
     	uint8_t exe_oem_info;
     	uint8_t exe_reserved2[10];
     	uint16_t  exe_e_lfanew;
};

void readBigEndian(uint8_t*,uint8_t *,int);
void readBigEndian(uint16_t*,uint8_t *,int);
void readBigEndian(uint32_t*,uint8_t *,int);
void readBigEndian(uint64_t*,uint8_t *,int);

void readLittleEndian(uint8_t*,uint8_t *,int);
void readLittleEndian(uint16_t*,uint8_t *,int);
void readLittleEndian(uint32_t*,uint8_t *,int);
void readLittleEndian(uint64_t*,uint8_t *,int);
void readFile(std::string);
void readExe64(std::string);


#ifndef EXE64
    #include "exe64.h"
#endif

#endif
