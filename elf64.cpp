#include "elf64.h"


Elf64::Elf64(std::string path)
{
    this->fd.open(path,std::ios::in|std::ios::binary);
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

void Elf64::read(uint8_t* to, uint8_t* from, uint8_t offset)
{
    if(this->id.ei_data == 1)//lsb
        readLittleEndian(to,from,offset);
    else if(this->id.ei_data == 2)//msb
        readBigEndian(to,from,offset);
    else
        ;//TODO: throw something to user
}

void Elf64::read(uint16_t* to, uint8_t* from, uint8_t offset)
{
    if(this->id.ei_data == 1)//lsb
        readLittleEndian(to,from,offset);
    else if(this->id.ei_data == 2)//msb
        readBigEndian(to,from,offset);
    else
        ;//TODO: throw something to user
}

void Elf64::read(uint32_t* to, uint8_t* from, uint8_t offset)
{
    if(this->id.ei_data == 1)//lsb
        readLittleEndian(to,from,offset);
    else if(this->id.ei_data == 2)//msb
        readBigEndian(to,from,offset);
    else
        ;//TODO: throw something to user
}

void Elf64::read(uint64_t* to, uint8_t* from, uint8_t offset)
{
    if(this->id.ei_data == 1)//lsb
        readLittleEndian(to,from,offset);
    else if(this->id.ei_data == 2)//msb
        readBigEndian(to,from,offset);
    else
        ;//TODO: throw something to user
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

    this->fd.seekg(offset,std::ios::beg);
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
    this->fd.seekg(strtab+header.sh_name,std::ios::beg);
    do
    {
        this->fd.read(&c,1);
        if(c != '\0')
			header.name += c;
    }while(c != '\0');

    unsigned int i;
    this->fd.seekg(header.sh_offset,std::ios::beg);
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
    this->fd.seekg(strtab,std::ios::beg);
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



uint32_t Elf64::getSection(std::string needle)
{
    uint32_t i;
    for(i = 0; i < this->sHeaders.size(); i++)
    {
        if(!this->sHeaders[i].name.compare(needle))
        {
            return i;
        }
    }
    return 0;
}

uint64_t Elf64::getSectionAddress(std::string needle)
{
	uint32_t i;
    for(i = 0; i < this->sHeaders.size(); i++)
    {
        if(!this->sHeaders[i].name.compare(needle))
        {
            return this->sHeaders[i].sh_addr;
        }
    }
    return 0;
}

void Elf64::disassemble(std::vector<std::pair<uint64_t, std::string>> &container)
{
	uint32_t index;
	uint64_t start_address;
	uint8_t target_architecture = 0;

	index = this->getSection(".text");
	start_address = this->sHeaders[index].sh_addr;
	std::vector<uint8_t> &machineCode = this->sHeaders[index].content;
	machine_to_opcode(container, machineCode,start_address,target_architecture);
	return;
}
