#include "elf32.h"


Elf32::Elf32(std::string path)
{
    this->fd.open(path,std::ios::in|std::ios::binary);
}

Elf32SH::~Elf32SH()
{
}

Elf32SH::Elf32SH()
{
    this->name = "";
}



void Elf32::readIdent()
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

void Elf32::read(uint8_t* to, uint8_t* from, uint8_t offset)
{
    if(this->id.ei_data == 1)//lsb
        readLittleEndian(to,from,offset);
    else if(this->id.ei_data == 2)//msb
        readBigEndian(to,from,offset);
    else
        ;//TODO: throw something to user
}

void Elf32::read(uint16_t* to, uint8_t* from, uint8_t offset)
{
    if(this->id.ei_data == 1)//lsb
        readLittleEndian(to,from,offset);
    else if(this->id.ei_data == 2)//msb
        readBigEndian(to,from,offset);
    else
        ;//TODO: throw something to user
}

void Elf32::read(uint32_t* to, uint8_t* from, uint8_t offset)
{
    if(this->id.ei_data == 1)//lsb
        readLittleEndian(to,from,offset);
    else if(this->id.ei_data == 2)//msb
        readBigEndian(to,from,offset);
    else
        ;//TODO: throw something to user
}

void Elf32::read(uint64_t* to, uint8_t* from, uint8_t offset)
{
    if(this->id.ei_data == 1)//lsb
        readLittleEndian(to,from,offset);
    else if(this->id.ei_data == 2)//msb
        readBigEndian(to,from,offset);
    else
        ;//TODO: throw something to user
}

void Elf32::readHeader()
{
    uint8_t buffer[36];
    this->fd.read((char *)&buffer,36);
    readLittleEndian(&(this->e_type),buffer,0);
    readLittleEndian(&(this->e_machine), buffer,2);
    readLittleEndian(&(this->e_version), buffer,4);
    readLittleEndian(&(this->e_entry), buffer,8);
    readLittleEndian(&(this->e_phoff), buffer, 12);
    readLittleEndian(&(this->e_shoff), buffer, 16);
    readLittleEndian(&(this->e_flags), buffer, 20);
    readLittleEndian(&(this->e_ehsize), buffer, 24);
    readLittleEndian(&(this->e_phentsize), buffer, 26);
    readLittleEndian(&(this->e_phnum), buffer, 28);
    readLittleEndian(&(this->e_shentsize), buffer, 30);
    readLittleEndian(&(this->e_shnum), buffer, 32);
    readLittleEndian(&(this->e_shstrndx), buffer, 34);

    return;
}

void Elf32::readSectionHeader(uint32_t offset, uint32_t strtab)
{
    uint8_t buffer[40];
    char c;
    Elf32SH header;

    this->fd.seekg(offset,std::ios::beg);
    this->fd.read((char *)buffer, 40);
    readLittleEndian(&(header.sh_name), buffer, 0);
    readLittleEndian(&(header.sh_type), buffer, 4);
    readLittleEndian(&(header.sh_flags), buffer, 8);
    readLittleEndian(&(header.sh_addr), buffer, 12);
    readLittleEndian(&(header.sh_offset), buffer, 16);
    readLittleEndian(&(header.sh_size), buffer, 20);
    readLittleEndian(&(header.sh_link), buffer, 24);
    readLittleEndian(&(header.sh_info), buffer, 28);
    readLittleEndian(&(header.sh_addralign), buffer, 32);
    readLittleEndian(&(header.sh_entsize), buffer, 36);
    
    header.name = "";
    //reading name
    this->fd.seekg(strtab+header.sh_name,std::ios::beg);
    do
    {
        this->fd.read(&c,1);
        if(c != '\0')
			header.name += c;
    }while(c != '\0');

    if(header.sh_type == 2 || header.sh_type == 11)
	{
		readSymbolTable(header);
	}

	/*If type of section is SHT_NOBITS then it has no data information on file*/
	if(header.sh_type != 8)
	{
		this->fd.seekg(header.sh_offset,fd.beg);
		header.content.resize(header.sh_size);
		this->fd.read((char *)&header.content[0], header.sh_size);
	}
    this->sHeaders.push_back(header);
}

void Elf32::readSectionHeaders()
{
	char c;
    uint8_t buf[4];
    uint16_t i;
    uint32_t index;
    uint64_t offset = this->e_shoff;
    uint64_t shstrtab = (this->e_shstrndx*this->e_shentsize) + this->e_shoff + 16;
    this->fd.seekg(shstrtab,std::ios::beg);
    this->fd.read((char *)buf,4);
    readLittleEndian(&shstrtab,buf,0);
    for(i = 0; i < this->e_shnum; i++)
    {
        readSectionHeader(offset,shstrtab);
        offset += this->e_shentsize;
    }

    std::vector<uint8_t> &dynstr = this->sHeaders[getSection(".dynstr")].content;
	std::vector<uint8_t> &strtab = this->sHeaders[getSection(".strtab")].content;
	/*read the names of symbols*/
	for(i = 0; i < this->dynamicSymbolTable.size(); i++)
	{
		std::string &name = this->dynamicSymbolTable[i].name;
		index = this->dynamicSymbolTable[i].st_name;
		do
		{
			c = dynstr[index++];
			if(c != '\0')
				name += c;
		}while(c != '\0');
	}

	for(i = 0; i < this->staticSymbolTable.size(); i++)
	{
		std::string &name = this->staticSymbolTable[i].name;
		index = this->staticSymbolTable[i].st_name;
		do
		{
			c = strtab[index++];
			if(c != '\0')
				name += c;
		}while(c != '\0');
	}
	return;

}

std::vector<std::string> Elf32::getSectionNames()
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
std::vector<uint8_t> Elf32::getSectionContent(std::string needle)
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

uint32_t Elf32::getSection(std::string needle)
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

uint32_t Elf32::getSectionAddress(std::string needle)
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

void Elf32::disassemble(std::vector<std::pair<uint64_t, std::string>> &container)
{
	uint8_t i;

	for(i = 0; i < this->sHeaders.size(); i++)
	{
		if(this->sHeaders[i].sh_flags & 4U)
		{
			container.push_back(std::make_pair(0xcafebabeUL, this->sHeaders[i].name));
			machine_to_opcode(container, this->sHeaders[i].content, this->sHeaders[i].sh_addr,1);
		}
	}
	return;
}


void Elf32::readSymbolTable(Elf32SH &section)
{
	/*TODO: test here*/;
	uint8_t buffer[16];
	uint64_t counter;

	if(section.sh_entsize != 16)
	{
		printf("Something seems wrong, trying to read wrong sized symbol table.");
		/*ERROR*/
	}

	this->fd.seekg(section.sh_offset,std::ios::beg);
	for(counter = 0; counter < section.sh_size; counter += 16)
	{
		struct Elf32_sym symHeader;

		this->fd.read((char *)&buffer,16);
		readLittleEndian(&(symHeader.st_name), buffer, 0);
		readLittleEndian(&(symHeader.st_value), buffer, 4);
		readLittleEndian(&(symHeader.st_size), buffer, 8);
		readLittleEndian(&(symHeader.st_info), buffer, 12);
		readLittleEndian(&(symHeader.st_other), buffer, 13);
		readLittleEndian(&(symHeader.st_shndx), buffer, 14);

		if(section.sh_type == 2)
			this->staticSymbolTable.push_back(symHeader);
		else if(section.sh_type == 11)
			this->dynamicSymbolTable.push_back(symHeader);
	}
}
