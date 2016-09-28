//
//  exe32.cpp
//  Exe
//
//  Created by İsmail Fırat Sezel on 28/09/16.
//  Copyright © 2016 İsmail Fırat Sezel. All rights reserved.
//

/*
#include "exe32.h"

Exe32::Exe32(std::string path)
{
    //this->st.contents = *new std::vector<uint8_t>();
    this->fd.open(path,std::ios::in|std::ios::binary);
}



void Exe32::readDosHeader()
{
    
    this->fd.read((char *)this->id.exe_magic,2);
    printf("Signature: %s\n", this->id.exe_magic);
    this->fd.read((char *)&this->id.exe_bytes_in_last_block,1);
    printf("bytes in last block: %u\n", this->id.exe_bytes_in_last_block);
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
    this->fd.read((char *)&this->id.exe_e_lfanew,1);//50
    
    this->fd.seekg(60, std::ios::beg);
   // this->fd.read((char *)&this->id.exe_pe_address, 4);
   // printf("pe address: %u\n", this->id.exe_pe_address);
    return;
}

void Exe32::readPESignature(){
  //  this->fd.seekg(this->id.exe_pe_address, std::ios::beg);
    this->fd.read((char *)&this->coff.Signature, 4);
    printf("coff signature: %u\n", this->coff.Signature);
    
    return;
}

void Exe32::readCoffHeader(){
  //  this->fd.seekg(this->id.exe_pe_address + 4, std::ios::beg);
    
    this->fd.read((char *)&this->coff.Machine,2);
    printf("coff machine: %x\n", this->coff.Machine);
    this->fd.read((char *)&this->coff.NumberOfSections,2);
    this->fd.read((char *)&this->coff.TimeDateStamp,4);
    this->fd.read((char *)&this->coff.PointerToSymbolTable,4);
    this->fd.read((char *)&this->coff.NumberOfSymbols,4);
    this->fd.read((char *)&this->coff.SizeOfOptionalHeader,2);
    printf("coff size of optional header: %u\n", this->coff.SizeOfOptionalHeader);
    this->fd.read((char *)&this->coff.Characteristics,2);
}

void Exe32::readSectionTable(){
  //  this->fd.seekg(this->id.exe_pe_address + 24 + this->coff.SizeOfOptionalHeader, std::ios::beg);
    this->fd.read((char *)&this->st.Name,8);
    this->fd.read((char *)&this->st.VirtualSize,4);
    this->fd.read((char *)&this->st.VirtualAddress,4);
    this->fd.read((char *)&this->st.SizeofRawData,4);
    this->fd.read((char *)&this->st.PointerToRawData,4);
 
    printf("section table name address: %llxx\n", this->st.Name);
    
    this->st.contents.resize(this->st.SizeofRawData);
    
    this->fd.seekg(this->st.PointerToRawData, std::ios::beg);
    this->fd.read((char *)&this->st.contents[0],this->st.SizeofRawData);
    
    
    return;
}


void Exe32::read(uint8_t* to, uint8_t* from, uint8_t offset)
{
    readLittleEndian(to,from,offset);
}

void Exe32::read(uint16_t* to, uint8_t* from, uint8_t offset)
{
    readLittleEndian(to,from,offset);
}

void Exe32::read(uint32_t* to, uint8_t* from, uint8_t offset)
{
    readLittleEndian(to,from,offset);
}

void Exe32::read(uint64_t* to, uint8_t* from, uint8_t offset)
{
    readLittleEndian(to,from,offset);
}

void Exe32::pointTobit(int offset){
    
}*/
