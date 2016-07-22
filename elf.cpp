#include "elf.h"

Elf64::Elf64(std::ifstream& desc) : fd(desc)
{
    
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
    //isimleri koyacan
    fd.seekg(strtab+header.sh_name,ios::beg);
    do
    {
        fd.read(&c,1);
        header.name += c;
    }while(c != '\0');
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

