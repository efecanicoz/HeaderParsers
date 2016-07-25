#include "elf.h"

/*Elf64::Elf64(std::ifstream& desc) : fd(desc)
{
    
}*/

Elf64::Elf64(std::string path)
{
    this->fd.open(path,ios::in|ios::binary);
}

Elf64SH::~Elf64SH()
{
    //no need to this, cpp handles this itself
    //this->content.~vector<uint8_t>();
}

Elf64SH::Elf64SH()
{
    this->name = "";
}



void Elf64::readIdent()
{
    this->fd.read((char *)this->id.ei_magic,4);
    this->fd.read((char *)&this->id.ei_class,1);
    this->fd.read((char *)&this->id.ei_data,1);
    this->fd.read((char *)&this->id.ei_version,1);
    this->fd.read((char *)&this->id.ei_osabi,1);
    this->fd.read((char *)&this->id.ei_abiversion,1);
    this->fd.read((char *)this->id.ei_pad,7);
    
    return; 
}

void Elf64::readHeader()
{
    uint8_t buffer[48];
    this->fd.read((char *)&buffer,48);
    readLittleEndian(&(this->e_type),buffer,0);
    readLittleEndian(&(this->e_machine), buffer,2);
    readLittleEndian(&(this->e_version), buffer,4);
    readLittleEndian(&(this->e_entry), buffer,8);
    readLittleEndian(&(this->e_phoff), buffer, 16);
    readLittleEndian(&(this->e_shoff), buffer, 24);
    readLittleEndian(&(this->e_flags), buffer, 32);
    readLittleEndian(&(this->e_ehsize), buffer, 36);
    readLittleEndian(&(this->e_phentsize), buffer, 38);
    readLittleEndian(&(this->e_phnum), buffer, 40);
    readLittleEndian(&(this->e_shentsize), buffer, 42);
    readLittleEndian(&(this->e_shnum), buffer, 44);
    readLittleEndian(&(this->e_shstrndx), buffer, 46);

    return;
}

void Elf64::readSectionHeader(uint64_t offset, uint64_t strtab)
{
    uint8_t buffer[64];
    char c;
    Elf64SH header;

    this->fd.seekg(offset,ios::beg);
    this->fd.read((char *)buffer, 64);
    readLittleEndian(&(header.sh_name), buffer, 0);
    readLittleEndian(&(header.sh_type), buffer, 4);
    readLittleEndian(&(header.sh_flags), buffer, 8);
    readLittleEndian(&(header.sh_addr), buffer, 16);
    readLittleEndian(&(header.sh_offset), buffer, 24);
    readLittleEndian(&(header.sh_size), buffer, 32);
    readLittleEndian(&(header.sh_link), buffer, 40);
    readLittleEndian(&(header.sh_info), buffer, 44);
    readLittleEndian(&(header.sh_addralign), buffer, 48);
    readLittleEndian(&(header.sh_entsize), buffer, 56);
    
    header.name = "";
    //reading name
    fd.seekg(strtab+header.sh_name,ios::beg);
    do
    {
        fd.read(&c,1);
        header.name += c;
    }while(c != '\0');

    unsigned int i;
    this->fd.seekg(offset,ios::beg);
    header.content.resize(header.sh_size);
    this->fd.read((char *)&header.content[0], header.sh_size);
    this->sHeaders.push_back(header);
}

void Elf64::readSectionHeaders()
{
    uint8_t buf[8];
    uint16_t i;
    uint64_t offset = this->e_shoff;
    uint64_t strtab = (this->e_shstrndx*this->e_shentsize) + this->e_shoff + 24; 
    this->fd.seekg(strtab,ios::beg);
    this->fd.read((char *)buf,8);
    readLittleEndian(&strtab,buf,0);
    for(i = 0; i < this->e_shnum; i++)
    {
        readSectionHeader(offset,strtab);
        offset += this->e_shentsize;
    }
    //strtab'dan sonra yazan 8 baytlık değeri fonksiyonlara gönderecen. 

}

std::vector<std::string> Elf64::getSectionNames()
{
    uint32_t i;
    std::vector<std::string> nameList;
    for(i = 0; i < this->sHeaders.size(); i++)
    {
        nameList.push_back(this->sHeaders[i].name);
    }
    return nameList;
}

//returns null if cant find desired name, but that statement should never be executed
std::vector<uint8_t> Elf64::getSectionContent(std::string needle)
{
    uint32_t i;
    for(i = 0; i < this->sHeaders.size(); i++)
    {
        if(!this->sHeaders[i].name.compare(needle))
        {
            return this->sHeaders[i].content;
        }
    }
    return std::vector<uint8_t>();
}
