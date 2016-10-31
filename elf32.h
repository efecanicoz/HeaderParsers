#ifndef READER
    #include "reader.h"
#endif
#ifndef ELF32
#define ELF32
#include <cstdint>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>

#include "EInterface.h"

//data uzunluklarını düzenle 64bit için geçerliler şu an..

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
        void read(uint8_t*,uint8_t*,uint8_t);
        void read(uint16_t*,uint8_t*,uint8_t);
        void read(uint32_t*,uint8_t*,uint8_t);
        void read(uint64_t*,uint8_t*,uint8_t);
 
        Elf32(std::string);
        void readHeader();
        void readIdent();
        void readSectionHeader(uint32_t, uint32_t);
        void readSectionHeaders();
        std::vector<uint8_t> getSectionContent(std::string);
		std::vector<std::string> getSectionNames();
        Elf32SH getSection(std::string);
        uint32_t getSectionAddress(std::string);
};

#endif
