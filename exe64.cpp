#include "exe64.h"

Exe64::Exe64(std::string path)
{
    //this->st.contents = *new std::vector<uint8_t>();
    this->fd.open(path,std::ios::in|std::ios::binary);
    this->buffer = std::vector<exe_section_table>();
}

/*sectionlar eklenecek*/

std::vector<uint8_t> Exe64::getHexSectionContent(std::string needle)
{
	uint32_t i;
	for(i = 0; i < this->buffer.size(); i++)
	{
		if(this->buffer[i].nameStr == needle)
			return this->buffer[i].contents;
	}
    return std::vector<uint8_t>();
}

std::string Exe64::getSectionContent(std::string needle, bool linearSweep)
{
    /*todo: fill*/
    return "";
}

std::vector<uint8_t> Exe64::getHexHeader()
{
    return std::vector<uint8_t>();
}

std::string Exe64::getHeaderInfo()
{
    /*todo: fill*/
    return "";
}

uint8_t Exe64::getSection(std::string needle)
{
	uint32_t i;
	for(i = 0; i < this->buffer.size(); i++)
	{
		if(this->buffer[i].nameStr == needle)
			return i;
	}
	return 0;
}


std::vector<std::string> Exe64::getSectionNames()
{
	std::vector<std::string> temp = std::vector<std::string>();
	uint32_t i;
	for(i = 0; i < this->buffer.size(); i++)
	{
		temp.push_back(this->buffer[i].nameStr);
	}
	return temp;
}

void Exe64::readDosHeader()
{
    uint8_t file_buffer[33];
    this->fd.read((char *)file_buffer, 33);
    readLittleEndian(&this->id.exe_magic, file_buffer, 0);
    readLittleEndian(&this->id.exe_bytes_in_last_block, file_buffer, 2);
    readLittleEndian(&this->id.exe_blocks_in_file, file_buffer, 3);
    readLittleEndian(&this->id.exe_num_relocs, file_buffer, 4);
    readLittleEndian(&this->id.exe_header_paragraphs, file_buffer, 5);
    readLittleEndian(&this->id.exe_min_extra_paragraphs, file_buffer, 6);
    readLittleEndian(&this->id.exe_max_extra_paragraphs, file_buffer, 7);
    readLittleEndian(&this->id.exe_ss, file_buffer, 8);
    readLittleEndian(&this->id.exe_sp, file_buffer, 9);
    readLittleEndian(&this->id.exe_checksum, file_buffer, 10);
    readLittleEndian(&this->id.exe_ip, file_buffer, 11);
    readLittleEndian(&this->id.exe_cs, file_buffer, 12);
    readLittleEndian(&this->id.exe_relocpos, file_buffer, 13);
    readLittleEndian(&this->id.exe_noverlay, file_buffer, 14);
    readLittleEndian(this->id.exe_reserved1, file_buffer, 18);
    readLittleEndian(&this->id.exe_oem_id, file_buffer, 19);
    readLittleEndian(&this->id.exe_oem_info, file_buffer, 20);
    readLittleEndian(this->id.exe_reserved2, file_buffer, 21);
    readLittleEndian(&this->id.exe_e_lfanew, file_buffer, 31);
    printf("Signature: %x\n", this->id.exe_magic);
    printf("bytes in last block: %u\n", this->id.exe_bytes_in_last_block);
    
    
    this->fd.seekg(60, std::ios::beg);
    uint8_t bufferPeAddress[4];
    this->fd.read((char *)bufferPeAddress, 4);
    
    readLittleEndian(&this->id.exe_pe_address, bufferPeAddress, 0);
    // this->fd.read((char *)&this->id.exe_pe_address, 4);
    printf("pe address: %u\n", this->id.exe_pe_address);

    return; 
}

void Exe64::readPESignature(){
    uint8_t bufferPeAddress[4];
    this->fd.seekg(this->id.exe_pe_address, std::ios::beg);
    this->fd.read((char *)bufferPeAddress, 4);
    
    readLittleEndian(&this->coff.Signature, bufferPeAddress, 0);
    
    printf("coff signature: %u\n", this->coff.Signature);
    
    return;
}

void Exe64::readCoffHeader(){
    
    this->fd.seekg(this->id.exe_pe_address + 4, std::ios::beg);
    uint8_t file_buffer[20];
    this->fd.read((char *)file_buffer, 20);
    readLittleEndian(&this->coff.Machine, file_buffer, 0);
    readLittleEndian(&this->coff.NumberOfSections, file_buffer, 2);
    readLittleEndian(&this->coff.TimeDateStamp, file_buffer, 4);
    readLittleEndian(&this->coff.PointerToSymbolTable, file_buffer, 8);
    readLittleEndian(&this->coff.NumberOfSymbols, file_buffer, 12);
    readLittleEndian(&this->coff.SizeOfOptionalHeader, file_buffer, 16);
    readLittleEndian(&this->coff.Characteristics, file_buffer, 18);
    if(this->coff.SizeOfOptionalHeader != 0)/*If this is an image file*/
	{
		uint8_t coff_buffer[28];
		this->fd.read((char *)coff_buffer, 28);

		readLittleEndian(&this->coff_fields.magic, coff_buffer, 0);
		readLittleEndian(&this->coff_fields.majorLinkerVersion,coff_buffer, 2);
		readLittleEndian(&this->coff_fields.minorLinkerVersion,coff_buffer, 3);
		readLittleEndian(&this->coff_fields.sizeOfCode,coff_buffer, 4);
		readLittleEndian(&this->coff_fields.sizeOfInitializedData,coff_buffer, 8);
		readLittleEndian(&this->coff_fields.sizeOfUninitializedData,coff_buffer, 12);
		readLittleEndian(&this->coff_fields.addressOfEntryPoint,coff_buffer, 16);
		readLittleEndian(&this->coff_fields.baseOfCode,coff_buffer, 20);
		readLittleEndian(&this->coff_fields.baseOfData,coff_buffer, 24);
	}

	printf("coff machine: %x\n", this->coff.Machine);
	printf("coff size of optional header: %u\n", this->coff.SizeOfOptionalHeader);
    
    return;
}

void Exe64::readSectionTable(){
    this->fd.seekg(this->id.exe_pe_address + 24 + this->coff.SizeOfOptionalHeader, std::ios::beg);
    uint8_t bufferSectionTable[40];
    
    this->buffer.resize(this->coff.NumberOfSections);
    
    uint8_t i;
    for(i = 0; i < this->coff.NumberOfSections; i++){
        this->fd.read((char *)bufferSectionTable, 40);
        
        this->buffer[i].nameStr = "";
        
        readLittleEndian(&this->buffer[i].Name, bufferSectionTable, 0);
        for(int j = 0; j < 8; j++){
            if((char)(bufferSectionTable[j]) == '\0')
                break;
            this->buffer[i].nameStr += (char)(bufferSectionTable[j]);
        }
        
        readLittleEndian(&this->buffer[i].VirtualSize, bufferSectionTable, 8);
        readLittleEndian(&this->buffer[i].VirtualAddress, bufferSectionTable, 12);
        readLittleEndian(&this->buffer[i].SizeofRawData, bufferSectionTable, 16);
        readLittleEndian(&this->buffer[i].PointerToRawData, bufferSectionTable, 20);
        readLittleEndian(&this->buffer[i].PointertoRelocations, bufferSectionTable, 24);
        readLittleEndian(&this->buffer[i].PointertoLineNumbers, bufferSectionTable, 28);
        readLittleEndian(&this->buffer[i].NumberofRelocations, bufferSectionTable, 32);
        readLittleEndian(&this->buffer[i].NumberofLineNumbers, bufferSectionTable, 34);
        readLittleEndian(&this->buffer[i].Characteristics, bufferSectionTable, 36);
    }
    
    uint8_t k;
    for(k = 0; k < this->coff.NumberOfSections; k++){
        
        this->buffer[k].contents.resize(this->buffer[k].SizeofRawData);
        
        //alinan content adresine gidiliyor ve conten cekiliyor
        this->fd.seekg(this->buffer[k].PointerToRawData, std::ios::beg);
        this->fd.read((char *)&this->buffer[k].contents[k],this->buffer[k].SizeofRawData);
    }
    
    //contentin icerigi bastiriliyor
    /*
     for(int i = 0 ; i < this->buffer[0].contents.size(); i++){
     printf("%x ", this->buffer[0].contents[i]);
     if(i % 8 == 0)
     printf("\n");
     }*/
    
    return;

}

void Exe64::disassemble(std::vector<std::pair<uint64_t, std::string>> &container)
{
    /*uint32_t index;
	uint64_t start_address;
	uint32_t deneme;
	uint8_t target_architecture = 0;

	index = this->getSection(".text");
	start_address = this->buffer[index].PointerToRawData;
	deneme = this->coff_fields.addressOfEntryPoint - this->coff_fields.baseOfCode;
	std::vector<uint8_t> &machineCode = this->buffer[index].contents;
	recursive_disassemble(machineCode,start_address ,target_architecture, deneme);
    return;*/

}

