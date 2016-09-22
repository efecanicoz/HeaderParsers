#include "exe64.h"

Exe64::Exe64(std::string path)
{
    this->fd.open(path,std::ios::in|std::ios::binary);
}

/*sectionlar eklenecek*/

void Exe64::readDosHeader()
{
    this->fd.read((char *)this->id.exe_magic,2);
    this->fd.read((char *)&this->id.exe_bytes_in_last_block,1);
    printf("bytes is last block: %u\n", this->id.exe_bytes_in_last_block);
    this->fd.read((char *)&this->id.exe_blocks_in_file,1);
    this->fd.read((char *)&this->id.exe_header_paragraphs,1);
    this->fd.read((char *)&this->id.exe_min_extra_paragraphs,1);
    this->fd.read((char *)&this->id.exe_max_extra_paragraphs,1);
    this->fd.read((char *)&this->id.exe_ss,1);
    this->fd.read((char *)&this->id.exe_sp,1);
    this->fd.read((char *)&this->id.exe_checksum,1);
    this->fd.read((char *)&this->id.exe_ip,1);
    this->fd.read((char *)&this->id.exe_cs,1);
    this->fd.read((char *)&this->id.exe_relocpos,1);
    this->fd.read((char *)&this->id.exe_noverlay,1);
    this->fd.read((char *)&this->id.exe_reserved1,4);
    this->fd.read((char *)&this->id.exe_oem_id,1);
    this->fd.read((char *)&this->id.exe_oem_info,1);
    this->fd.read((char *)this->id.exe_reserved2,10);
    this->fd.read((char *)&this->id.exe_e_lfanew,1);

    return; 
}

void Exe64::read(uint8_t* to, uint8_t* from, uint8_t offset)
{
    readLittleEndian(to,from,offset);
}

void Exe64::read(uint16_t* to, uint8_t* from, uint8_t offset)
{  
    readLittleEndian(to,from,offset);  
}

void Exe64::read(uint32_t* to, uint8_t* from, uint8_t offset)
{  
    readLittleEndian(to,from,offset);
}

void Exe64::read(uint64_t* to, uint8_t* from, uint8_t offset)
{
    readLittleEndian(to,from,offset);
}
