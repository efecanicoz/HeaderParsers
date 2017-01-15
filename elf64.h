#ifndef ELF64
#define ELF64

#include "reader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <list>
#include "EInterface.h"
#include "disassemble.h"
#include "svg.h"


class Elf64SH
{

    public:
        uint32_t sh_name;
        std::string name;
        uint32_t sh_type;
        uint64_t sh_flags;
        uint64_t sh_addr;
        uint64_t sh_offset;
        uint64_t sh_size;
        uint32_t sh_link;
        uint32_t sh_info;
        uint64_t sh_addralign;
        uint64_t sh_entsize;
        std::vector<uint8_t> content;
        Elf64SH();
        ~Elf64SH();
};

class Elf64 : public ExecutableFile
{
	private:
		struct Elf64_sym
		{
			std::string name;
			uint32_t    st_name;
			uint8_t 	st_info;
			uint8_t 	st_other;
			uint16_t    st_shndx;
			uint64_t    st_value;
			uint64_t    st_size;
		};
        typedef struct {
            uint64_t	r_offset;
            uint64_t	r_info;
        } Elf64_Rel;

        typedef struct {
            uint64_t	r_offset;
            uint64_t	r_info;
            int64_t	r_addend;
        } Elf64_Rela;

    public:
        struct e_ident id;
        std::ifstream fd;
        uint16_t e_type;
        uint16_t e_machine;
        uint32_t e_version;
        uint64_t e_entry;
        uint64_t e_phoff;
        uint64_t e_shoff;
        uint32_t e_flags;
        uint16_t e_ehsize;
        uint16_t e_phentsize;
        uint16_t e_phnum;
        uint16_t e_shentsize;
        uint16_t e_shnum;
        uint16_t e_shstrndx;
        uint64_t strtab;
        std::vector<Elf64SH> sHeaders;
        std::vector<struct Elf64_sym> staticSymbolTable;
        std::vector<struct Elf64_sym> dynamicSymbolTable;
        std::vector<Elf64_Rel> relList;
        std::vector<Elf64_Rela> relaList;

        void read(uint8_t*,uint8_t*,uint8_t);
        void read(uint16_t*,uint8_t*,uint8_t);
        void read(uint32_t*,uint8_t*,uint8_t);
        void read(uint64_t*,uint8_t*,uint8_t);
 
        Elf64(std::ifstream&);
        Elf64(std::string);
        void readHeader();
        void readIdent();
        void readSectionHeader(uint64_t, uint64_t);
        void readSectionHeaders();
        void readSymbolTable(Elf64SH &);

        std::vector<std::string> getSectionNames();
        uint32_t getSection(std::string);
		uint64_t getSectionAddress(std::string);
		void disassemble(std::vector<std::pair<uint64_t, std::string>> &);
		void disassembleAll(std::vector<std::pair<uint64_t, std::string>> &);

        std::string getRelaInfo();
        std::string getRelInfo();
        std::string getStringTableInfo(Elf64SH &);

        std::vector<uint8_t> getHexHeader();
        std::string getHeaderInfo();
        std::vector<uint8_t> getHexSectionContent(std::string needle);
        std::string getSectionContent(std::string, bool);


        void create_svg(std::string);
};

#endif
