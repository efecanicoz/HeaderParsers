#include "fileReader.h"

static const uint8_t ELF_H[4] = {0x7F,0x45,0x4C,0x46};
static const uint8_t EXE_H[2] = {0x4D,0x5A};

ExecutableFile* readElf32(std::string fd)
{
    Elf32* bucket = new Elf32(fd);
    bucket->readIdent();
    bucket->readHeader();
    bucket->readSectionHeaders();
    std::vector<std::string> secNames = bucket->getSectionNames();
    return bucket;
}

ExecutableFile* readElf64(std::string fd)
{
    Elf64* bucket = new Elf64(fd);
    bucket->readIdent();
    bucket->readHeader();
    bucket->readSectionHeaders();
    std::vector<std::string> secNames = bucket->getSectionNames();

    /*
    result = bucket.getSection(neym);

    machine_to_opcode(result.content, result.sh_addr);
    */
    return bucket;
}


ExecutableFile* readExe32(std::string fd)
{
    Exe32* bucket = new Exe32(fd);
    bucket->readDosHeader();
    bucket->readPESignature();
    bucket->readCoffHeader();
    bucket->readSectionTable();
    return bucket;
}

ExecutableFile* readExe64(std::string fd)
{
    Exe64* bucket = new Exe64(fd);
    bucket->readDosHeader();
    bucket->readPESignature();
    bucket->readCoffHeader();
    bucket->readSectionTable();
    return bucket;
}

ExecutableFile* readFile(const std::string path)
{

	uint8_t buffer[4];
    std::ifstream fd(path, std::ios::in|std::ios::binary);
    fd.read((char *)&buffer[0],4);
    for(int i = 0; i < 4; i++)
    {
        printf("%x %x\n",buffer[i],ELF_H[i]);
    }
    if(buffer[0] == ELF_H[0] && buffer[1] == ELF_H[1] && buffer[2] == ELF_H[2] && buffer[3] == ELF_H[3])
    {
        uint8_t ei_class;
        fd.read((char *)&ei_class,1);
        fd.close();
        if(ei_class == 1)
            return readElf32(path);
        else if(ei_class == 2)
            return readElf64(path);
    }
    else if(buffer[0] == EXE_H[0] && buffer[1] == EXE_H[1])
    {
        uint32_t exePeAddress;
        uint16_t machine;

    	fd.seekg(60, std::ios::beg);
		fd.read((char *)&exePeAddress, 4);

		fd.seekg(exePeAddress + 4, std::ios::beg);

		fd.read((char *)&machine,2);
		printf("Machine:: %u\n", machine);

		if(machine == 332)
		{
			return readExe32(path);
		}
		else
		{
			return readExe64(path);
		}
    }
    else
        printf("üzüldük");

    return NULL;
}
