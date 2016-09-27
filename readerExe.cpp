#include "readerExe.h"

const std::vector<uint8_t> EXE_H = {0x4D,0x5A};

void readBigEndian(uint8_t *to, uint8_t from[], int offset)
{
    *to = from[offset];
}
void readBigEndian(uint16_t *to, uint8_t from[], int offset)
{
    *to = from[offset]<<8 
        |from[offset+1];
}
void readBigEndian(uint32_t *to, uint8_t from[], int offset)
{
    *to = from[offset]<<24
        |from[offset+1]<<16
        |from[offset+2]<<8
        |from[offset+3];
}
void readBigEndian(uint64_t *to, uint8_t from[], int offset)
{
    *to = (static_cast<uint64_t>(from[offset]) << 56) |
        (static_cast<uint64_t>(from[offset+1]) << 48) |
        (static_cast<uint64_t>(from[offset+2]) << 40) |
        (static_cast<uint64_t>(from[offset+3]) << 32) |
        (static_cast<uint64_t>(from[offset+4]) << 24) |
        (static_cast<uint64_t>(from[offset+5]) << 16) |
        (static_cast<uint64_t>(from[offset+6]) <<  8) |
        (static_cast<uint64_t>(from[offset+7])) ; 
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

void readExe64(std::string fd)
{
    Exe64 bucket(fd);
    bucket.readDosHeader();
    bucket.readPESignature();
    bucket.readCoffHeader();
    bucket.readSectionTable();
    /*bucket.readSectionHeaders();
    std::vector<std::string> secNames = bucket.getSectionNames();
    int i;
    for(i = 0; i < secNames.size(); i++)
    {
        std::cout << secNames[i];
    }*/
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
    std::vector<uint8_t> buffer(2);
    
    std::ifstream fd(path, std::ios::in|std::ios::binary);
    fd.read((char *)&buffer[0],2);
    
    //fd.seekg(0);
    if(buffer == EXE_H)
    {
        /*32 bit eklenecek*/
        readExe64(path);
    }
    else
        printf("üzüldük");

    return;
}




