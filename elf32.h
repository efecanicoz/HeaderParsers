#ifndef ELF32
#define ELF32

#include "reader.h"
#include <cstdint>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>

#include "disassemble.h"
#include "EInterface.h"
#include "svg.h"


class Elf32SH
{

    public:
        uint32_t sh_name;
        std::string   name;
        uint32_t sh_type;
        uint32_t sh_flags;
        uint32_t sh_addr;
        uint32_t sh_offset;
        uint32_t sh_size;
        uint32_t sh_link;
        uint32_t sh_info;
        uint32_t sh_addralign;
        uint32_t sh_entsize;
        std::vector<uint8_t> content;
        Elf32SH();
        ~Elf32SH();
};


class Elf32 : public ExecutableFile
{
	private:
		struct Elf32_sym
		{
			std::string name;
			uint32_t    st_name;
			uint32_t   	st_value;
			uint32_t    st_size;
			uint8_t 	st_info;
			uint8_t 	st_other;
			uint16_t    st_shndx;
		};

        typedef struct {
            uint32_t	r_offset;
            uint32_t	r_info;
        } Elf32_Rel;

        typedef struct {
            uint32_t	r_offset;
            uint32_t	r_info;
            int32_t	r_addend;
        } Elf32_Rela;

    public:
        struct e_ident id;
        std::ifstream fd;
        uint16_t e_type;
        uint16_t e_machine;
        uint32_t e_version;
        uint32_t e_entry;
        uint32_t e_phoff;
        uint32_t e_shoff;
        uint32_t e_flags;
        uint16_t e_ehsize;
        uint16_t e_phentsize;
        uint16_t e_phnum;
        uint16_t e_shentsize;
        uint16_t e_shnum;
        uint16_t e_shstrndx;
        uint32_t strtab;
        std::vector<Elf32SH> sHeaders;
        std::vector<Elf32_Rel> relList;
        std::vector<Elf32_Rela> relaList;
        std::vector<struct Elf32_sym> staticSymbolTable;
        std::vector<struct Elf32_sym> dynamicSymbolTable;

        void read(uint8_t*,uint8_t*,uint8_t);
        void read(uint16_t*,uint8_t*,uint8_t);
        void read(uint32_t*,uint8_t*,uint8_t);
        void read(uint64_t*,uint8_t*,uint8_t);
 
        Elf32(std::string);
        void readHeader();
        void readIdent();
        void readSectionHeader(uint32_t, uint32_t);
        void readSectionHeaders();
        void readSymbolTable(Elf32SH &);
        void disassembleAll(std::vector<std::pair<uint64_t, std::string>> &);

        std::string getRelaInfo();
        std::string getRelInfo();
        std::string getStringTableInfo(Elf32SH &);

		std::vector<std::string> getSectionNames();
        uint32_t getSection(std::string);
        uint32_t getSectionAddress(std::string);
		void disassemble(std::vector<std::pair<uint64_t, std::string>> &);

        std::string getHeaderInfo();
        std::vector<uint8_t> getHexHeader();
        std::vector<uint8_t> getHexSectionContent(std::string needle);
        std::string getSectionContent(std::string, bool);

        void create_svg(std::string);
};

#endif
