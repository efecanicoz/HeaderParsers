#include "exe64.h"
#include "Display.h"

#include <iostream>
#include <string>
#include <map>

#ifndef Node_h
#include "Node.h"
#endif

#ifndef Point_h
#include "Point.h"
#endif

using namespace svg;

void CreateRect(int width, int height, int x, int y, Document doc);
void svg_create(std::map<uint64_t, Block> block_table);
int returnNumberofMap(std::string name, std::map<std::string, int> mymap);
Points Location(std::string name,  std::vector<Node> nodes);

Dimensions dimensions(20000, 20000);
std::vector<Node> nodes;//holds all rectangels

Document doc("/home/firat/Desktop/my_svg.svg", Layout(dimensions, Layout::TopLeft));
std::map<std::string,int> mymap;
std::map<std::string,int>::iterator it;
std::map<uint64_t, Block>::iterator blockite;
std::vector<Node>::iterator n;

Node cachenode;
Node nod, linkNod, link2Nod;
Points current;


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
  /*
    uint32_t index;
    uint64_t start_address;
    uint32_t deneme;
    uint8_t target_architecture = 0;

    index = this->getSection(".text");
    start_address = this->buffer[index].PointerToRawData;
    deneme = this->coff_fields.addressOfEntryPoint - this->coff_fields.baseOfCode;
    std::vector<uint8_t> &machineCode = this->buffer[index].contents;
    std::map<uint64_t, Block> block_table;
    block_table = recursive_disassemble(machineCode,start_address ,target_architecture, deneme);
    svg_create(block_table);
	return;*/

}

void svg_create(std::map<uint64_t, Block> block_table){
    printf("Enter the Function.");
    Block block;
    Polygon border(Stroke(1, Color::Red));

    current.x = 50;/*location of current point*/
    current.y = 50;
    int countforFunctions = 0;

    std::string node = "";
    int countfory = 10;


    for (blockite = block_table.begin(); blockite!=block_table.end(); ++blockite){
        block = blockite->second;
        nod.name = std::to_string(block.start_address);//adresi string yap

        Points locCur = Location(nod.name, nodes);
        //int num = returnNumberofMap(node, mymap);
        if(locCur.x == -1 && locCur.y == -1){
            //mymap.insert ( std::pair<std::string,int>(Names[k],k));
            countforFunctions++;
            nod.location = current;
            nod.Link = std::to_string(block.jump1);
            nod.Link2 = std::to_string(block.jump2);
            nodes.push_back(nod);

            doc << Rectangle(Point(nod.location.x, nod.location.y), 80, 80, Color::Yellow);
            doc << Text(Point(nod.location.x, nod.location.y), nod.name, Color::Red, Font(15, "Verdana"));

            countfory -= 1;
            current.x += 100;

            if(countfory == 0){
                current.y += 90;
                current.x = 50;
                countfory = 10;
            }
        }else{
            countforFunctions++;
            nod.location.x = locCur.x;
            nod.location.y = locCur.y;
            nod.Link = std::to_string(block.jump1);
            nod.Link2 = std::to_string(block.jump2);
        }

        std::string link1 = std::to_string(block.jump1);
        std::string link2 = std::to_string(block.jump2);

        if(1){//link varsa
            Polyline polyline1(Stroke(.5, Color::Green));
            if(nod.name.compare(nod.Link) == 0){
                //recursive
                doc << Circle(Point(nod.location.x + 40, nod.location.y + 40), 60, Fill(Color(100, 200, 120)),
                              Stroke(1, Color(200, 250, 150)));
            }else{
                //drew already?
                Points locCur = Location(nod.Link, nodes);
                if(locCur.x == -1 && locCur.y == -1){
                    //new, create link node
                    linkNod.name = nod.Link;
                    linkNod.location = current;
                    nodes.push_back(linkNod);

                    doc << Rectangle(Point(linkNod.location.x, linkNod.location.y), 80, 80, Color::Yellow);
                    doc << Text(Point(linkNod.location.x, linkNod.location.y), linkNod.name, Color::Red, Font(15, "Verdana"));

                    polyline1 << Point(current.x, current.y + 20) << Point(nod.location.x  , nod.location.y + 20);
                    doc << polyline1;

                    countfory -= 1;
                    current.x += 100;

                    if(countfory == 0){
                        current.y += 90;
                        current.x = 50;
                        countfory = 3;
                    }
                }else{
                    //used before
                    polyline1 << Point(nod.location.x + 80, nod.location.y + 20) << Point(locCur.x , locCur.y + 20);
                    doc << polyline1;
                }
            }
        }
        if(1){//link2 if link2 is not empty
            Polyline polyline1(Stroke(.5, Color::Red));
            if(nod.name.compare(nod.Link2) == 0){
                //recursive
                doc << Circle(Point(nod.location.x + 40, nod.location.y + 40), 60, Fill(Color(100, 200, 120)),
                              Stroke(1, Color(200, 250, 150)));
            }else{
                //drew already
                Points locCur = Location(nod.Link2, nodes);
                if(locCur.x == -1 && locCur.y == -1){
                    //new, create link node
                    link2Nod.name = link2;
                    link2Nod.location = current;
                    nodes.push_back(link2Nod);

                    doc << Rectangle(Point(link2Nod.location.x, link2Nod.location.y), 80, 80, Color::Yellow);
                    doc << Text(Point(link2Nod.location.x, link2Nod.location.y), link2Nod.name, Color::Red, Font(15, "Verdana"));

                    polyline1 << Point(current.x, current.y + 60) << Point(nod.location.x , nod.location.y + 60);
                    doc << polyline1;

                    countfory -= 1;
                    current.x += 100;

                    if(countfory == 0){
                        current.y += 90;
                        current.x = 50;
                        countfory = 3;
                    }
                }
                else{
                    //DEMEKKİ DAHA ÖNCEDEN KULLANILMIŞ
                    polyline1 << Point(nod.location.x + 80, nod.location.y + 60) << Point(locCur.x , locCur.y + 60);
                    doc << polyline1;
                }
            }
        }

        /*if (nod.name.compare(cachenode.name) != 0){
         doc << Rectangle(Point(nod.location.x, nod.location.y), 80, 80, Color::Yellow);
         doc << Text(Point(nod.location.x, nod.location.y), nod.name, Color::Red, Font(15, "Verdana"));

         Polyline polyline1(Stroke(.5, Color::Red));
         if(cachenode.name.compare("") != 0){
         polyline1 << Point(current.x, current.y + 40) << Point(cachenode.location.x + 80, cachenode.location.y + 40);
         doc << polyline1;
         }
         cachenode = nod;
         countfory -= 1;
         current.x += 100;
         }*/

        /*if(locCur.x == cachenode.location.x && locCur.y == cachenode.location.y){//recursive alert
         doc << Circle(Point(nod.location.x + 40, nod.location.y + 40), 60, Fill(Color(100, 200, 120)), Stroke(1, Color(200, 250, 150)));
         }else{
         cachenode = nod;
         int xyer = (num % 3) + 1;
         int yyer = (num / 3) + 1;

         xyer = xyer * 50;
         yyer = yyer * 90;
         Polyline polyline1(Stroke(.5, Color::Red));

         polyline1 << Point(current.x, current.y + 40) << Point(xyer - 20, yyer + 40);
         doc << polyline1;
         }*/




        if(countfory == 0){
            current.y += 90;
            current.x = 50;
            countfory = 3;
        }

    }
    //doc << Circle(Point(80, 80), 20, Fill(Color(100, 200, 120)), Stroke(1, Color(200, 250, 150)));


    //doc << (Polygon(Color(200, 160, 220), Stroke(.5, Color(150, 160, 200))) << Point(20, 70)
    //        << Point(25, 72) << Point(33, 70) << Point(35, 60) << Point(25, 55) << Point(18, 63));
    doc.save();
}


int returnNumberofMap(std::string name, std::map<std::string, int> mymap){
    for (it=mymap.begin(); it!=mymap.end(); ++it){
        if(it->first.compare(name) == 0)
            return it->second;
    }
    return -1;
}

Points Location(std::string name,  std::vector<Node> nodes){
    Points p;
    p.x = -1;
    p.y = -1;
    for (n=nodes.begin(); n!=nodes.end(); ++n){
        if(n->name.compare(name) == 0)
            return n->location;
    }
    return p;
}


