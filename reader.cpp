#include "reader.h"
#include <vector>
#include <list>

const vector<uint8_t> ELF_H = {0x7F,0x45,0x4C,0x46};

struct e_ident readElfIdent(ifstream& fd)
{
    struct e_ident id;
    fd.read((char *)id.ei_magic,4);
    fd.read((char *)&id.ei_class,1);
    fd.read((char *)&id.ei_data,1);
    fd.read((char *)&id.ei_version,1);
    fd.read((char *)&id.ei_osabi,1);
    fd.read((char *)&id.ei_abiversion,1);
    fd.read((char *)id.ei_pad,7);
    
    return id;
}

void readLittleEndian(uint8_t *to, uint8_t from[], int offset)
{
    *to = from[offset];
}
void readLittleEndian(uint16_t *to, uint8_t from[], int offset)
{
    *to = from[offset] 
        |from[offset+1]<<8;
}
void readLittleEndian(uint32_t *to, uint8_t from[], int offset)
{
    *to = from[offset]
        |from[offset+1]<<8
        |from[offset+2]<<16
        |from[offset+3]<<24;
}
void readLittleEndian(uint64_t *to, uint8_t from[], int offset)
{
    *to = (static_cast<uint64_t>(from[offset]) <<  0) |
        (static_cast<uint64_t>(from[offset+1]) <<  8) |
        (static_cast<uint64_t>(from[offset+2]) << 16) |
        (static_cast<uint64_t>(from[offset+3]) << 24) |
        (static_cast<uint64_t>(from[offset+4]) << 32) |
        (static_cast<uint64_t>(from[offset+5]) << 40) |
        (static_cast<uint64_t>(from[offset+6]) << 48) |
        (static_cast<uint64_t>(from[offset+7]) << 56) ; 
}

struct e64_header readElf64Header(ifstream& fd)
{
    struct e64_header header;
    uint8_t buffer[48];
    fd.read((char *)&buffer,48);
    readLittleEndian(&(header.e_type),buffer,0);
    readLittleEndian(&(header.e_machine), buffer,2);
    readLittleEndian(&(header.e_version), buffer,4);
    readLittleEndian(&(header.e_entry), buffer,8);
    readLittleEndian(&(header.e_phoff), buffer, 16);
    readLittleEndian(&(header.e_shoff), buffer, 24);
    readLittleEndian(&(header.e_flags), buffer, 32);
    readLittleEndian(&(header.e_ehsize), buffer, 36);
    readLittleEndian(&(header.e_phentsize), buffer, 38);
    readLittleEndian(&(header.e_phnum), buffer, 40);
    readLittleEndian(&(header.e_shentsize), buffer, 42);
    readLittleEndian(&(header.e_shnum), buffer, 44);
    readLittleEndian(&(header.e_shstrndx), buffer, 46);
    
    //printf("%x   %x   %x   \n%x      %x   %x\n",header.e_phoff, header.e_phentsize,header.e_phnum,header.e_shoff,header.e_shentsize,header.e_shnum);
    return header;
}

struct e64_section_header read64Section(ifstream& fd, uint64_t offset, uint64_t shstr_offset)
{
    fd.seekg(offset, ios::beg);
    uint8_t buffer[64];
    char c;
    struct e64_section_header secHeader;
    fd.read((char *)buffer,64);
    readLittleEndian(&(secHeader.sh_name), buffer, 0);
    readLittleEndian(&(secHeader.sh_type), buffer, 4);
    readLittleEndian(&(secHeader.sh_flags), buffer, 8);
    readLittleEndian(&(secHeader.sh_addr), buffer, 16);
    readLittleEndian(&(secHeader.sh_offset), buffer, 24);
    readLittleEndian(&(secHeader.sh_size), buffer, 32);
    readLittleEndian(&(secHeader.sh_link), buffer, 40);
    readLittleEndian(&(secHeader.sh_info), buffer, 44);
    readLittleEndian(&(secHeader.sh_addralign), buffer, 48);
    readLittleEndian(&(secHeader.sh_entsize), buffer, 56);
    
    secHeader.name = "";
    if(secHeader.sh_name != 0)
    {
        fd.seekg(secHeader.sh_name + shstr_offset , ios::beg);
        do
        {
            fd.read(&c,1);
            secHeader.name += c;
        }while(c != '\0');
    }
    return secHeader;
}

struct e32_section_header read32Section(ifstream& fd, uint32_t offset, uint32_t shstr_offset)
{
    fd.seekg(offset);
    uint8_t buffer[40];
    char c;
    struct e32_section_header secHeader;
    fd.read((char *)buffer, 40);
    readLittleEndian(&(secHeader.sh_name), buffer, 0);
    readLittleEndian(&(secHeader.sh_type), buffer, 4);
    readLittleEndian(&(secHeader.sh_flags), buffer, 8);
    readLittleEndian(&(secHeader.sh_addr), buffer, 12);
    readLittleEndian(&(secHeader.sh_offset), buffer, 16);
    readLittleEndian(&(secHeader.sh_size), buffer, 20);
    readLittleEndian(&(secHeader.sh_link), buffer, 24);
    readLittleEndian(&(secHeader.sh_info), buffer, 28);
    readLittleEndian(&(secHeader.sh_addralign), buffer, 32);
    readLittleEndian(&(secHeader.sh_entsize), buffer, 36);
    
    secHeader.name = "";
    if(secHeader.sh_name != 0)
    {
        fd.seekg(secHeader.sh_name + shstr_offset, ios::beg);
        do
        {
            fd.read(&c, 1);
            secHeader.name += c;
        }while(c != '\0');
    }
    return secHeader;
}

void readStringTable(ifstream& fd, uint64_t offset, uint64_t size)
{
    unsigned int i;
    uint64_t adr = 0L;
    string temp;
    fd.seekg(offset,ios::beg);
    vector<uint8_t> buffer(size);
    std::list<std::pair<uint64_t, std::string> > strtab;
    
    fd.read((char *)&buffer[0], size);
    for(i = 0; i < buffer.size(); i++)
    {
        if(buffer[i] == '\0')
        {
            //append string to list
            strtab.push_back(make_pair(adr,temp));
            temp = "";
            adr = i + 1;
        }
        else
        {
            temp += buffer[i];
        }
    }
    return;
}

void readSectionContent(ifstream& fd, uint64_t offset, uint64_t size)
{
    unsigned int i;
    fd.seekg(offset,ios::beg);
    vector<uint8_t> buffer(size);
    fd.read((char *)&buffer[0],size);
    return;
}

void readElf32Header(ifstream& fd)
{
    struct e32_header header;
/*    fd.read((char *)header.e_type,2);
    fd.read((char *)header.e_machine,2); 
    fd.read((char *)header.e_version,4); 
    fd.read((char *)header.e_entry,4); 
    fd.read((char *)header.e_phoff,4); 
    fd.read((char *)header.e_shoff,4); 
    fd.read((char *)header.e_flags,4); 
    fd.read((char *)header.e_ehsize,2); 
    fd.read((char *)header.e_phentsize,2); 
    fd.read((char *)header.e_phnum,2); 
    fd.read((char *)header.e_shentsize,2); 
    fd.read((char *)header.e_shnum,2); 
    fd.read((char *)header.e_shstrndx,2);
*/
    return;
}

void readElf(ifstream& fd)
{
    struct e_ident identifier = readElfIdent(fd);
    if(identifier.ei_class == 1)
    {
        readElf32Header(fd);
    }
    else if(identifier.ei_class == 2)
    {
        uint64_t offset;
        struct e64_header elf_header;
        elf_header = readElf64Header(fd);
        struct e64_section_header strTable = read64Section(fd,(elf_header.e_shstrndx*elf_header.e_shentsize)+elf_header.e_shoff,0);
        elf_header.strtab = strTable.sh_offset;
        vector<struct e64_section_header> sHeaders;
        offset = elf_header.e_shoff;
        for(int i=0; i < elf_header.e_shnum; i++)
        {
            printf("Trying to read, offset: %lu\n", offset);
            struct e64_section_header secHeader = read64Section(fd, offset, elf_header.strtab);
            sHeaders.push_back(secHeader);
            offset += elf_header.e_shentsize;
            printf("readed a section header, contents:\n");
            printf("Address of name: %lu\n", secHeader.sh_name);
            printf("Name: %s\n", secHeader.name.c_str());
            printf("Type: %u\n", secHeader.sh_type);
            printf("Flags: %lu\n", secHeader.sh_flags);
            printf("Address: %lu\n", secHeader.sh_addr);
            printf("Offset: %lu\n", secHeader.sh_offset);
            printf("Size: %lu\n", secHeader.sh_size);
            printf("Link: %u\n", secHeader.sh_link);
            printf("Info: %d\n", secHeader.sh_info);
            printf("Address Align: %lu\n", secHeader.sh_addralign);
            printf("Entry size: %lu\n", secHeader.sh_entsize);
            printf("End of header\n\n");
            if(secHeader.sh_type == 3)
            {
                readStringTable(fd,secHeader.sh_offset,secHeader.sh_size);
            }
            else
                readSectionContent(fd,secHeader.sh_offset,secHeader.sh_size);

        }
    }
    else
        printf("error");
    


    return;
}

string readFile(const string path)
{
    vector<uint8_t> buffer(4);
    
    ifstream fd(path, ios::in|ios::binary);
    fd.read((char *)&buffer[0],4);
    for(int i = 0; i < 4; i++)
    {
        printf("%x %x\n",buffer[i],ELF_H[i]);
    }
    fd.seekg(0);
    if(buffer == ELF_H)
        readElf(fd);
    else
        printf("üzüldük");
    string a = "elf";

    return a;
}
