#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <vector>     //for vector
#include <iterator>   //for std::istream_iterator and std::ostream_iterator
#include <algorithm>  //for std::copy

using namespace std;

string exeSig = "MZ";


struct DOS_Header
 {
     unsigned short bytes_in_last_block;
     unsigned short blocks_in_file;
     unsigned short num_relocs;
     unsigned short header_paragraphs;
     unsigned short min_extra_paragraphs;
     unsigned short max_extra_paragraphs;
     unsigned short ss;
     unsigned short sp;
     unsigned short checksum;
     unsigned short ip;
     unsigned short cs;
     unsigned short reloc_table_offset;
     unsigned short overlay_number;
     /*uint32_t lastsize;
     uint32_t nblocks;
     uint32_t nreloc;
     uint32_t hdrsize;
     uint32_t minalloc;
     uint32_t maxalloc;
     void *ss;
     void *sp;
     short checksum;
     void *ip;
     void *cs;
     short relocpos;
     short noverlay;
     short reserved1[4];
     short oem_id;
     short oem_info;
     short reserved2[10];
     long  e_lfanew;*/
     unsigned int exOff;
 };

DOS_Header exeh;

unsigned char* readUnBoundedBytes(DOS_Header exef, int endOff, vector<unsigned char>& buf){
    vector<unsigned char> uBoundedByteBuf(buf.begin() + exef.exOff, buf.begin() + + exef.exOff + endOff);
    exef.exOff += endOff;

    return reinterpret_cast<unsigned char*>(uBoundedByteBuf.data());
}

unsigned char* readByte(DOS_Header exef, vector<unsigned char>& buf){

    vector<unsigned char> oneByteBuf(buf.begin() + exef.exOff, buf.begin() + exef.exOff + 1);
    exef.exOff += 1;

    return reinterpret_cast<unsigned char*>(oneByteBuf.data());
}

unsigned char* read2Bytes(int bOff, vector<unsigned char>& buf){

    vector<unsigned char> twoByteBuf(buf.begin() + bOff, buf.begin() + bOff + 2);

    return reinterpret_cast<unsigned char*>(twoByteBuf.data());
}

unsigned char* read4Bytes(int bOff, vector<unsigned char>& buf){

    vector<unsigned char> fourByteBuf(buf.begin() + bOff, buf.begin() + bOff + 4);
    exef.exOff += 4;

    return reinterpret_cast<unsigned char*>(fourByteBuf.data());
}

unsigned char* read8Bytes(int bOff, vector<unsigned char>& buf){

    vector<unsigned char> eightByteBuf(buf.begin() + bOff, buf.begin() + bOff + 8);
    exef.exOff += 8;

    return reinterpret_cast<unsigned char*>(eightByteBuf.data());
}

unsigned char* read16Bytes(int bOff, vector<unsigned char>& buf){

    vector<unsigned char> oneSixByteBuf(buf.begin() + bOff, buf.begin() + bOff + 16);
    exef.exOff += 16;

    return reinterpret_cast<unsigned char*>(oneSixByteBuf.data());
}

unsigned char* read32Bytes(int bOff, vector<unsigned char>& buf){

    vector<unsigned char> threeTwoByteBuf(buf.begin() + bOff, buf.begin() + bOff + 32);
    exef.exOff += 32;

    return reinterpret_cast<unsigned char*>(threeTwoByteBuf.data());
}


int readSignature(vector<unsigned char>& buf){

    std::string str(buf.begin(), buf.begin() + 2);
    cout << str;
    if(str.compare(exeSig) == 0) return 1;

    return 0;
}

void readDosHeader(vector<unsigned char>& buf, DOS_Header exeh){

    //exeh.lastsize = boost::lexical_cast<short> ();
    std::stringstream ss;

    exeh.bytes_in_last_block = std::atoi( reinterpret_cast<char( & )[sizeof(read2Bytes(2, buf))]>( read2Bytes(2, buf) ) );
    exeh.blocks_in_file = std::atoi( reinterpret_cast<char( & )[sizeof(read2Bytes(0, buf))]>( read2Bytes(0, buf) ) );
    exeh.num_relocs = std::atoi( reinterpret_cast<char( & )[sizeof(read2Bytes(0, buf))]>( read2Bytes(0, buf) ) );
    exeh.header_paragraphs = std::atoi( reinterpret_cast<char( & )[sizeof(read2Bytes(0, buf))]>( read2Bytes(0, buf) ) );
    exeh.min_extra_paragraphs = std::atoi( reinterpret_cast<char( & )[sizeof(read2Bytes(0, buf))]>( read2Bytes(0, buf) ) );
    exeh.max_extra_paragraphs = std::atoi( reinterpret_cast<char( & )[sizeof(read2Bytes(0, buf))]>( read2Bytes(0, buf) ) );


    /*cout << hex << n;

    for(int i=0; i<2; ++i)
        ss << hex << (unsigned int)data[i];
    string mystr = ss.str();

    cout << mystr;*/
}

int main (int argc, char *argv[])
{
    string path = argv[1];

    ifstream fd(path, ios::in|ios::binary);

    std::istream_iterator<unsigned char> begin(fd), end;
    std::vector<unsigned char> buffer(begin, end);

    if(readSignature(buffer)) { readDosHeader(buffer, exeh); }
    else {cout << "fail";}


    /*std::copy(buffer.begin(),
              buffer.end(),
              std::ostream_iterator<unsigned int>(std::cout << hex, ","));*/

}


