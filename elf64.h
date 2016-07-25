#ifndef READER
    #include "reader.h"
#endif
#ifndef ELF64

#define ELF64
#include <cstdint>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>

class Elf64SH
{
    public:
        uint32_t sh_name;
        std::string   name;
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


class Elf64
{
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

        Elf64(std::ifstream&);
        Elf64(std::string);
        void readHeader();
        void readIdent();
        void readSectionHeader(uint64_t, uint64_t);
        void readSectionHeaders();
        std::vector<std::string> getSectionNames();
        std::vector<uint8_t> getSectionContent(std::string);
};
#endif
