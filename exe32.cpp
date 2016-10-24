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
    //this->st.contents = std::vector<uint8_t>();
    this->fd.open(path,std::ios::in|std::ios::binary);
    this->buffer = std::vector<exe_section_table>();
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
    
    return;
}

void Exe32::readSectionTable(){
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
        
        this->buffer[i].contents.resize(this->buffer[i].SizeofRawData);
        
        //alinan content adresine gidiliyor ve conten cekiliyor
        this->fd.seekg(this->buffer[i].PointerToRawData, std::ios::beg);
        this->fd.read((char *)&this->buffer[i].contents[i],this->buffer[i].SizeofRawData);
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
