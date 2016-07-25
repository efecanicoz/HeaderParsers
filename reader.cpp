#include "reader.h"

const std::vector<uint8_t> ELF_H = {0x7F,0x45,0x4C,0x46};

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

/*void readStringTable(ifstream& fd, uint64_t offset, uint64_t size)
{
    unsigned int i;
    uint64_t adr = 0L;
    string temp;
    fd.seekg(offset,std::ios::beg);
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
    fd.seekg(offset,std::ios::beg);
    vector<uint8_t> buffer(size);
    fd.read((char *)&buffer[0],size);
    return;
}

*/

void readElf32(std::string fd)
{
    Elf32 bucket(fd);
    bucket.readIdent();
    bucket.readHeader();
    bucket.readSectionHeaders();
    std::vector<std::string> secNames = bucket.getSectionNames();
    int i;
    for(i = 0; i < secNames.size(); i++)
    {
        std::cout << secNames[i];
    }
}

void readElf64(std::string fd)
{
    Elf64 bucket(fd);
    bucket.readIdent();
    bucket.readHeader();
    bucket.readSectionHeaders();
    std::vector<std::string> secNames = bucket.getSectionNames();
    int i;
    for(i = 0; i < secNames.size(); i++)
    {
        std::cout << secNames[i];
    }
    /*struct e_ident identifier = readElfIdent(fd);
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
    */


    return;
}

void readFile(const std::string path)
{
    std::vector<uint8_t> buffer(4);
    
    std::ifstream fd(path, std::ios::in|std::ios::binary);
    fd.read((char *)&buffer[0],4);
    for(int i = 0; i < 4; i++)
    {
        printf("%x %x\n",buffer[i],ELF_H[i]);
    }
    //fd.seekg(0);
    if(buffer == ELF_H)
    {
        uint8_t ei_class;
        fd.read((char *)&ei_class,1);
        fd.close();
        if(ei_class == 1)
            readElf32(path);
        else if(ei_class == 2)
            readElf64(path);
    }
    else
        printf("üzüldük");

    return;
}
