//
//  exe32.cpp
//  Exe
//
//  Created by İsmail Fırat Sezel on 28/09/16.
//  Copyright © 2016 İsmail Fırat Sezel. All rights reserved.
//


#include "exe32.h"

Exe32::Exe32(std::string path)
{
    //this->st.contents = *new std::vector<uint8_t>();
    this->fd.open(path,std::ios::in|std::ios::binary);
}



void Exe32::readDosHeader()
{
    
    uint8_t buffer[33];
    this->fd.read((char *)buffer, 33);
    readLittleEndian(&this->id.exe_magic, buffer, 0);
    readLittleEndian(&this->id.exe_bytes_in_last_block, buffer, 2);
    readLittleEndian(&this->id.exe_blocks_in_file, buffer, 3);
    readLittleEndian(&this->id.exe_num_relocs, buffer, 4);
    readLittleEndian(&this->id.exe_header_paragraphs, buffer, 5);
    readLittleEndian(&this->id.exe_min_extra_paragraphs, buffer, 6);
    readLittleEndian(&this->id.exe_max_extra_paragraphs, buffer, 7);
    readLittleEndian(&this->id.exe_ss, buffer, 8);
    readLittleEndian(&this->id.exe_sp, buffer, 9);
    readLittleEndian(&this->id.exe_checksum, buffer, 10);
    readLittleEndian(&this->id.exe_ip, buffer, 11);
    readLittleEndian(&this->id.exe_cs, buffer, 12);
    readLittleEndian(&this->id.exe_relocpos, buffer, 13);
    readLittleEndian(&this->id.exe_noverlay, buffer, 14);
    readLittleEndian(this->id.exe_reserved1, buffer, 18);
    readLittleEndian(&this->id.exe_oem_id, buffer, 19);
    readLittleEndian(&this->id.exe_oem_info, buffer, 20);
    readLittleEndian(this->id.exe_reserved2, buffer, 21);
    readLittleEndian(&this->id.exe_e_lfanew, buffer, 31);
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

void Exe32::readPESignature(){
    uint8_t bufferPeAddress[4];
    this->fd.seekg(this->id.exe_pe_address, std::ios::beg);
    this->fd.read((char *)bufferPeAddress, 4);
    
    readLittleEndian(&this->coff.Signature, bufferPeAddress, 0);
    
    printf("coff signature: %u\n", this->coff.Signature);
    
    return;
}

void Exe32::readCoffHeader(){
    this->fd.seekg(this->id.exe_pe_address + 4, std::ios::beg);
    uint8_t buffer[20];
    this->fd.read((char *)buffer, 20);
    readLittleEndian(&this->coff.Machine, buffer, 0);
    readLittleEndian(&this->coff.NumberOfSections, buffer, 2);
    readLittleEndian(&this->coff.TimeDateStamp, buffer, 4);
    readLittleEndian(&this->coff.PointerToSymbolTable, buffer, 8);
    readLittleEndian(&this->coff.NumberOfSymbols, buffer, 12);
    readLittleEndian(&this->coff.SizeOfOptionalHeader, buffer, 16);
    readLittleEndian(&this->coff.Characteristics, buffer, 18);

    printf("coff machine: %x\n", this->coff.Machine);
    printf("coff size of optional header: %u\n", this->coff.SizeOfOptionalHeader);

}

void Exe32::readSectionTable(){
    this->fd.seekg(this->id.exe_pe_address + 24 + this->coff.SizeOfOptionalHeader, std::ios::beg);
    uint8_t bufferSectionTable[24];
    this->fd.read((char *)bufferSectionTable, 24);
    
    
    readLittleEndian(&this->st.Name, bufferSectionTable, 0);
    readLittleEndian(&this->st.VirtualSize, bufferSectionTable, 8);
    readLittleEndian(&this->st.VirtualAddress, bufferSectionTable, 12);
    readLittleEndian(&this->st.SizeofRawData, bufferSectionTable, 16);
    readLittleEndian(&this->st.PointerToRawData, bufferSectionTable, 20);


 
    printf("section table name address: %llxx\n", this->st.Name);
    printf("section table size of raw data: %x\n", this->st.SizeofRawData);
    
    this->st.contents.resize(this->st.SizeofRawData);
    
    this->fd.seekg(this->st.PointerToRawData, std::ios::beg);
    
    this->fd.read((char *)&this->st.contents[0],this->st.SizeofRawData);
    
    for(int i = 0 ; i < this->st.contents.size(); i++){
        printf("%x ", this->st.contents[i]);
        if(i % 8 == 0)
            printf("\n");
    }
    
    
    
    return;
}

