#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdint>

using namespace std;

struct e_ident
{
    uint8_t ei_magic[4];
    uint8_t ei_class;
    uint8_t ei_data;
    uint8_t ei_version;
    uint8_t ei_osabi;
    uint8_t ei_abiversion;
    uint8_t ei_pad[7];
};

struct e32_section_header
{
    uint32_t sh_name;
    string   name;
    uint32_t sh_type;
    uint32_t sh_flags;
    uint32_t sh_addr;
    uint32_t sh_offset;
    uint32_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint32_t sh_addralign;
    uint32_t sh_entsize;
};

struct e64_section_header
{
    uint32_t sh_name;
    string   name;
    uint32_t sh_type;
    uint64_t sh_flags;
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;
};


struct e32_program_header
{
    uint32_t p_type;
    uint32_t p_offset;
    uint32_t p_vaddr;
    uint32_t p_paddr;
    uint32_t p_filesz;
    uint32_t p_memsz;
    uint32_t p_flags;
    uint32_t p_align;
};

struct e32_header
{
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
    uint32_t e_strtab;
};

struct e64_header
{
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
};

void readLittleEndian(uint8_t*,uint8_t *,int);
void readLittleEndian(uint16_t*,uint8_t *,int);
void readLittleEndian(uint32_t*,uint8_t *,int);
void readLittleEndian(uint64_t*,uint8_t *,int);
struct e_ident readElfIdent(ifstream&);
void readElf32Header(ifstream&); //doldur bunu
e64_header readElf64Header(ifstream&);
struct e32_section_header read32Section(ifstream&, uint32_t, uint32_t);
struct e64_section_header read64Section(ifstream&, uint64_t, uint64_t);
string readFile(string);
