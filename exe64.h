#ifndef EXE64
#define EXE64

#include <cstdint>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "reader.h"
#include <ctime>
#include "block.h"
#include "svg.h"

#include "EInterface.h"
#include "disassemble.h"

#ifndef EXE_STRUCT
#define EXE_STRUCT
	struct exe_ident {
        uint16_t exe_magic;
        uint16_t exe_bytes_in_last_block;
        uint16_t exe_blocks_in_file;
        uint16_t exe_num_relocs;
        uint16_t exe_header_paragraphs;
        uint16_t exe_min_extra_paragraphs;
        uint16_t exe_max_extra_paragraphs;
        uint16_t exe_ss;
        uint16_t exe_sp;
        uint16_t exe_checksum;
        uint16_t exe_ip;
        uint16_t exe_cs;
        uint16_t exe_relocpos;
        uint16_t exe_noverlay;
        uint16_t  exe_e_lfanew;
        uint32_t exe_pe_address;
	};

	/*Coff Header*/
	struct exe_coff {
		uint32_t Signature;
		uint16_t Machine;
		uint16_t NumberOfSections;
		uint32_t TimeDateStamp;
		uint32_t PointerToSymbolTable;
		uint32_t NumberOfSymbols;
		uint16_t SizeOfOptionalHeader;
		uint16_t Characteristics;
	};

	struct exe_coff_fields
	{
		uint16_t magic;
		uint8_t  majorLinkerVersion;
		uint8_t  minorLinkerVersion;
		uint32_t sizeOfCode;
		uint32_t sizeOfInitializedData;
		uint32_t sizeOfUninitializedData;
		uint32_t addressOfEntryPoint;
		uint32_t baseOfCode;
		uint32_t baseOfData;
	};

	/*section Table Header*/
	struct exe_section_table {
		uint64_t Name;
		std::string nameStr;
		std::vector<uint8_t> contents;
		uint32_t VirtualSize;
		uint32_t VirtualAddress;
		uint32_t SizeofRawData;
		uint32_t PointerToRawData;
		uint32_t PointertoRelocations;
		uint32_t PointertoLineNumbers;
		uint16_t NumberofRelocations;
		uint16_t NumberofLineNumbers;
		uint32_t Characteristics;
	};
#endif



class Exe64 : public ExecutableFile
{
    public:
        struct exe_ident id;
        struct exe_coff  coff;
        struct exe_section_table st;
		struct exe_coff_fields coff_fields;
        std::vector<exe_section_table> buffer;
        std::ifstream fd;
/*Section eklenecek*/
    
 
        Exe64(std::ifstream&);
        Exe64(std::string);
        
        void readDosHeader();
        void readPESignature();
        void readCoffHeader();
        void readSectionTable();
 /*Section eklenecek*/
 
        std::vector<uint8_t> getHexSectionContent(std::string);
		std::vector<std::string> getSectionNames();
        uint8_t getSection(std::string needle);

        std::string getHeaderInfo();
        std::vector<uint8_t> getHexHeader();
        std::string getSectionContent(std::string, bool);


        void create_svg(std::string);
};
#endif
