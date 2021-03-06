#include "exe64.h"

Exe64::Exe64(std::string path)
{
    //this->st.contents = *new std::vector<uint8_t>();
    this->fd.open(path,std::ios::in|std::ios::binary);
    this->buffer = std::vector<exe_section_table>();
}

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

std::vector<uint8_t> Exe64::getHexHeader()
{
    std::vector<uint8_t> file_buffer(376);
    this->fd.seekg(0,std::ios::beg);
    this->fd.read((char *)&file_buffer[0], 376);
    return file_buffer;
}

std::string Exe64::getHeaderInfo()
{
    std::stringstream ss;
    std::string temp_string = "";
    ss << "DOS header: \n";
    ss << "\tMagic bytes: "<< std::hex << std::showbase << id.exe_magic << "\n";
    ss << "\tImage size mod 512: "<< std::hex << std::showbase << id.exe_bytes_in_last_block << "\n";
    ss << "\tNumber of blocks in the file: " << std::hex << std::showbase << id.exe_blocks_in_file << "\n";
    ss << "\tNumber of relocation entries: " << std::hex << std::showbase << id.exe_num_relocs << "\n";
    ss << "\tNumber of paragraphs in header: " << std::hex << std::showbase << id.exe_header_paragraphs << "\n";
    ss << "\tMinimum required memory" << std::hex << std::showbase << id.exe_min_extra_paragraphs << "\n";
    ss << "\tMaximum required memory: " << std::hex << std::showbase << id.exe_max_extra_paragraphs << "\n";
    ss << "\tRelative value of stack segment: " << std::hex << std::showbase << id.exe_ss << "\n";
    ss << "\tInitial value of sp register: " << std::hex << std::showbase << id.exe_sp << "\n";
    ss << "\tFile checksum: " << std::hex << std::showbase << id.exe_checksum << "\n";
    ss << "\tInitial value of ip register: " << std::hex << std::showbase << id.exe_ip << "\n";
    ss << "\tInitial value of cs register: " << std::hex << std::showbase << id.exe_cs << "\n";
    ss << "\tOffset of first relocation item: " << std::hex << std::showbase << id.exe_relocpos << "\n";
    ss << "\tOverlay number: " << std::hex << std::showbase << id.exe_noverlay << "\n";

    ss << "COFF header: \n";
    ss << "\tSignature: " << std::hex << std::showbase << coff.Signature << "\n";
    switch (coff.Machine)
    {
    case 0x0:
        temp_string = "Any";
        break;
    case 0x1D3:
        temp_string = "Matsushita AM33";
        break;
    case 0x8664:
        temp_string = "x64";
        break;
    case 0x1C0:
        temp_string = "ARM little endian";
        break;
    case 0xAA64:
        temp_string = "ARM64 little endian";
        break;
    case 0x1C4:
        temp_string = "ARM Thumb-2 little endian";
        break;
    case 0xEBC:
        temp_string = "EFI byte code";
        break;
    case 0x14C:
        temp_string = "Intel 386 and successors";
        break;
    case 0x200:
        temp_string = "Intel Itanium";
        break;
    case 0x9041:
        temp_string = "Mitsubishi M32R little endian";
        break;
    case 0x266:
        temp_string = "MIPS16";
        break;
    case 0x366:
        temp_string = "MIPS with FPU";
        break;
    case 0x466:
        temp_string = "MIPS16 with FPU";
        break;
    case 0x1F0:
        temp_string = "Power PC little endian";
        break;
    case 0x1F1:
        temp_string = "Power PC with floating point support";
        break;
    case 0x166:
        temp_string = "MIPS little endian";
        break;
    case 0x5032:
        temp_string = "RISC-V 32-bit address space";
        break;
    case 0x5064:
        temp_string = "RISC-V 64-bit address space";
        break;
    case 0x5128:
        temp_string = "RISC-V 128-bit address space";
        break;
    case 0x1A2:
        temp_string = "Hitachi SH3";
        break;
    case 0x1A3:
        temp_string = "Hitachi SH3 DSP";
        break;
    case 0x1A6:
        temp_string = "Hitachi SH4";
        break;
    case 0x1A8:
        temp_string = "Hitachi SH5";
        break;
    case 0x1C2:
        temp_string = "Thumb";
        break;
    case 0x169:
        temp_string = "MIPS little-endian WCE v2";
        break;
    default:
        temp_string = "Machine unknown";
        break;
    }
    ss << "\tMachine: " << temp_string << "\n";
    ss << "\tNuber of sections: " << coff.NumberOfSections << "\n";
     long int timeLong = coff.TimeDateStamp;
    ss << "\tTimeDateStamp: " << std::asctime(std::localtime(&timeLong)) << "\n";
    ss << "\tAddress of symbol table: " << std::hex << std::showbase << coff.PointerToSymbolTable << "\n";
    ss << "\tNumber of symbols: " << coff.NumberOfSymbols;
    ss << "\tSize of optional header: " << coff.SizeOfOptionalHeader << "\n";
    temp_string = "";
    if(coff.Characteristics & 0x0001)
        temp_string += "IMAGE_FILE_RELOCS_STRIPPED ";
    if(coff.Characteristics & 0x0002)
        temp_string += "IMAGE_FILE_EXECUTABLE_IMAGE ";
    if(coff.Characteristics & 0x0004)
        temp_string += "IMAGE_FILE_LINE_NUMS_STRIPPED ";
    if(coff.Characteristics & 0x0008)
        temp_string += "IMAGE_FILE_LOCAL_SYMS_STRIPPED ";
    if(coff.Characteristics & 0x0010)
        temp_string += "IMAGE_FILE_AGGRESSIVE_WS_TRIM ";
    if(coff.Characteristics & 0x0020)
        temp_string += "IMAGE_FILE_LARGE_ADDRESS_AWARE ";
    if(coff.Characteristics & 0x0040)
        temp_string += "RESERVED ";
    if(coff.Characteristics & 0x0080)
        temp_string += "IMAGE_FILE_BYTES_REVERSED_LO ";
    if(coff.Characteristics & 0x0100)
        temp_string += "IMAGE_FILE_32BIT_MACHINE ";
    if(coff.Characteristics & 0x0200)
        temp_string += "IMAGE_FILE_DEBUG_STRIPPED ";
    if(coff.Characteristics & 0x0400)
        temp_string += "IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP ";
    if(coff.Characteristics & 0x0800)
        temp_string += "IMAGE_FILE_NET_RUN_FROM_SWAP ";
    if(coff.Characteristics & 0x1000)
        temp_string += "IMAGE_FILE_SYSTEM ";
    if(coff.Characteristics & 0x2000)
        temp_string += "IMAGE_FILE_DLL ";
    if(coff.Characteristics & 0x4000)
        temp_string += "IMAGE_FILE_UP_SYSTEM_ONLY ";
    if(coff.Characteristics & 0x8000)
        temp_string += "IMAGE_FILE_BYTES_REVERSED_HI ";
    ss << "\tCharacteristics: " << temp_string << "\n";

    ss << "Optional Header:\n";
    ss << "\tMagic number: " << ((coff_fields.magic == 0x10B) ? "PE32\n" : "PE32+\n");
    ss << "\tMajor linker version: " << std::hex << std::showbase << coff_fields.majorLinkerVersion << "\n";
    ss << "\tMinor linker version: " << std::hex << std::showbase << coff_fields.minorLinkerVersion << "\n";
    ss << "\tSize of code section: " << coff_fields.sizeOfCode << "\n";
    ss << "\tSize of initialized data: " << coff_fields.sizeOfInitializedData << "\n";
    ss << "\tSize of uninitialized data: " << coff_fields.sizeOfUninitializedData << "\n";
    ss << "\tAddress of entry point: " << coff_fields.addressOfEntryPoint << "\n";
    ss << "\tBase of code: " << coff_fields.baseOfCode << "\n";
    ss << "\tBase of data: " << coff_fields.baseOfData << "\n";

    return ss.str();
}

std::string Exe64::getSectionContent(std::string needle, bool linearSweep)
{
    uint8_t sectionIndex;
    std::stringstream ss;
    std::string temp_string = "";
    std::vector<std::pair<uint64_t,std::string>> container = std::vector<std::pair<uint64_t,std::string>>();

    sectionIndex = getSection(needle);
    exe_section_table &section = this->buffer[sectionIndex];
    ss << "Section Header Info\n";
    ss << "Name: " << section.nameStr << "\n";
    ss << "Virtual size: " << section.VirtualSize << "\n";
    ss << "Virtual address:" << std::hex << std::showbase << section.VirtualAddress << "\n";
    ss << "Size of raw data: " << section.SizeofRawData << "\n";
    ss << "Pointer to raw data: " << std::hex << std::showbase << section.PointerToRawData << "\n";
    ss << "Pointer to relocations: " << std::hex << std::showbase << section.PointertoRelocations << "\n";
    ss << "Pointer to line numbers: " << std::hex << std::showbase << section.PointertoLineNumbers << "\n";
    ss << "Number of relocations: " << section.NumberofRelocations << "\n";
    ss << "Number of line numbers: " << section.NumberofLineNumbers << "\n";
    temp_string = "";
    if(section.Characteristics & 0x00000000)
        temp_string += "Reserved ";
    if(section.Characteristics & 0x00000001)
        temp_string += "Reserved ";
    if(section.Characteristics & 0x00000002)
        temp_string += "Reserved ";
    if(section.Characteristics & 0x00000004)
        temp_string += "Reserved ";
    if(section.Characteristics & 0x00000008)
        temp_string += "IMAGE_SCN_TYPE_NO_PAD ";
    if(section.Characteristics & 0x00000010)
        temp_string += "Reserved ";
    if(section.Characteristics & 0x00000020)
        temp_string += "IMAGE_SCN_CNT_CODE ";
    if(section.Characteristics & 0x00000040)
        temp_string += "IMAGE_SCN_CNT_INITIALIZED_DATA ";
    if(section.Characteristics & 0x00000080)
        temp_string += "IMAGE_SCN_CNT_UNINITIALIZED_DATA ";
    if(section.Characteristics & 0x00000100)
        temp_string += "IMAGE_SCN_LNK_OTHER ";
    if(section.Characteristics & 0x00000200)
        temp_string += "IMAGE_SCN_LNK_INFO ";
    if(section.Characteristics & 0x00000400)
        temp_string += "Reserved ";
    if(section.Characteristics & 0x00000800)
        temp_string += "IMAGE_SCN_LNK_REMOVE ";
    if(section.Characteristics & 0x00001000)
        temp_string += "IMAGE_SCN_LNK_COMDAT ";
    if(section.Characteristics & 0x00002000)
        temp_string += "Reserved ";
    if(section.Characteristics & 0x00004000)
        temp_string += "Reserved ";
    if(section.Characteristics & 0x00008000)
        temp_string += "IMAGE_SCN_GPREL ";
    if(section.Characteristics & 0x00010000)
        temp_string += "IMAGE_SCN_MEM_PURGEABLE ";
    if(section.Characteristics & 0x00020000)
        temp_string += "IMAGE_SCN_MEM_16BIT ";
    if(section.Characteristics & 0x00040000)
        temp_string += "IMAGE_SCN_MEM_LOCKED ";
    if(section.Characteristics & 0x00080000)
        temp_string += "IMAGE_SCN_MEM_PRELOAD ";
    switch ((section.Characteristics & 0x00F00000) >> 20 )
    {
    case 0:
        temp_string += " ";
        break;
    case 1:
        temp_string += "IMAGE_SCN_ALIGN_1BYTES ";
        break;
    case 2:
        temp_string += "IMAGE_SCN_ALIGN_2BYTES ";
        break;
    case 3:
        temp_string += "IMAGE_SCN_ALIGN_4BYTES ";
        break;
    case 4:
        temp_string += "IMAGE_SCN_ALIGN_8BYTES ";
        break;
    case 5:
        temp_string += "IMAGE_SCN_ALIGN_16BYTES ";
        break;
    case 6:
        temp_string += "IMAGE_SCN_ALIGN_32BYTES ";
        break;
    case 7:
        temp_string += "IMAGE_SCN_ALIGN_64BYTES ";
        break;
    case 8:
        temp_string += "IMAGE_SCN_ALIGN_128BYTES ";
        break;
    case 9:
        temp_string += "IMAGE_SCN_ALIGN_256BYTES ";
        break;
    case 10:
        temp_string += "IMAGE_SCN_ALIGN_512BYTES ";
        break;
    case 11:
        temp_string += "IMAGE_SCN_ALIGN_1024BYTES ";
        break;
    case 12:
        temp_string += "IMAGE_SCN_ALIGN_2048BYTES ";
        break;
    case 13:
        temp_string += "IMAGE_SCN_ALIGN_4096BYTES ";
        break;
    case 14:
        temp_string += "IMAGE_SCN_ALIGN_8192BYTES ";
        break;
    default:
        temp_string += "";
        break;
    }
    if(section.Characteristics & 0x01000000)
        temp_string += "IMAGE_SCN_LNK_NRELOC_OVFL ";
    if(section.Characteristics & 0x02000000)
        temp_string += "IMAGE_SCN_MEM_DISCARDABLE ";
    if(section.Characteristics & 0x04000000)
        temp_string += "IMAGE_SCN_MEM_NOT_CACHED ";
    if(section.Characteristics & 0x08000000)
        temp_string += "IMAGE_SCN_MEM_NOT_PAGED ";
    if(section.Characteristics & 0x10000000)
        temp_string += "IMAGE_SCN_MEM_SHARED ";
    if(section.Characteristics & 0x20000000)
        temp_string += "IMAGE_SCN_MEM_EXECUTE ";
    if(section.Characteristics & 0x40000000)
        temp_string += "IMAGE_SCN_MEM_READ ";
    if(section.Characteristics & 0x80000000)
        temp_string += "IMAGE_SCN_MEM_WRITE ";
    ss << "Characteristics: " << temp_string << "\n";

    ss << "-----------------------------------------------\n";

    if(section.Characteristics & 0x00000020)/*if it has code inside*/
    {
        disassemble_content(container, section.contents, section.PointerToRawData, 0, coff_fields.addressOfEntryPoint - coff_fields.baseOfCode, linearSweep );
        for(auto &line: container)
        {
            ss << std::hex << std:: showbase << line.first << "\t" << line.second << "\n";
        }
    }
    return ss.str();
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
    uint8_t buffer[28];
    this->fd.read((char *)buffer, 28);
    readLittleEndian(&this->id.exe_magic, buffer, 0);
    readLittleEndian(&this->id.exe_bytes_in_last_block, buffer, 2);
    readLittleEndian(&this->id.exe_blocks_in_file, buffer, 4);
    readLittleEndian(&this->id.exe_num_relocs, buffer, 6);
    readLittleEndian(&this->id.exe_header_paragraphs, buffer, 8);
    readLittleEndian(&this->id.exe_min_extra_paragraphs, buffer, 10);
    readLittleEndian(&this->id.exe_max_extra_paragraphs, buffer, 12);
    readLittleEndian(&this->id.exe_ss, buffer, 14);
    readLittleEndian(&this->id.exe_sp, buffer, 16);
    readLittleEndian(&this->id.exe_checksum, buffer, 18);
    readLittleEndian(&this->id.exe_ip, buffer, 20);
    readLittleEndian(&this->id.exe_cs, buffer, 22);
    readLittleEndian(&this->id.exe_relocpos, buffer, 24);
    readLittleEndian(&this->id.exe_noverlay, buffer, 26);
    
    
    this->fd.seekg(60, std::ios::beg);
    uint8_t bufferPeAddress[4];
    this->fd.read((char *)bufferPeAddress, 4);
    
    readLittleEndian(&this->id.exe_pe_address, bufferPeAddress, 0);

    return; 
}

void Exe64::readPESignature(){
    uint8_t bufferPeAddress[4];
    this->fd.seekg(this->id.exe_pe_address, std::ios::beg);
    this->fd.read((char *)bufferPeAddress, 4);
    
    readLittleEndian(&this->coff.Signature, bufferPeAddress, 0);
    
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

    return;

}

void Exe64::create_svg(std::string section_name)
{
    exe_section_table &section = this->buffer[getSection(section_name)];
    std::map<uint64_t, Block> block_table = get_blocks(section.contents, section.PointerToRawData, 0, coff_fields.addressOfEntryPoint - coff_fields.baseOfCode);

    svg_create(block_table);
}
