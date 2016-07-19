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
// short is 2 bytes, long is 4 bytes
     char signature[2];
     short lastsize;
     short nblocks;
     short nreloc;
     short hdrsize;
     short minalloc;
     short maxalloc;
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
     long  e_lfanew;
     unsigned int exOff;
 };

DOS_Header exeh;

unsigned char* readUnBoundedBytes(int beginOff, int endOff, vector<unsigned char>& buf){
    vector<unsigned char> uBoundedByteBuf(buf.begin() + exef.exOff, buf.begin() + + exef.exOff + endOff);
    exef.exOff += endOff;

    return reinterpret_cast<unsigned char*>(uBoundedByteBuf.data());
}

unsigned char* readByte(DOS_Header exef, vector<unsigned char>& buf){

    vector<unsigned char> oneByteBuf(buf.begin() + exef.exOff, buf.begin() + + exef.exOff + 1);
    exef.exOff += 1;

    return reinterpret_cast<unsigned char*>(oneByteBuf.data());
}

unsigned char* read2Bytes(DOS_Header exef, vector<unsigned char>& buf){

    vector<unsigned char> twoByteBuf(buf.begin() + exef.exOff, buf.begin() + + exef.exOff + 2);
    exef.exOff += 2;

    return reinterpret_cast<unsigned char*>(twoByteBuf.data());
}

unsigned char* read4Bytes(DOS_Header exef, vector<unsigned char>& buf){

    vector<unsigned char> fourByteBuf(buf.begin() + exef.exOff, buf.begin() + + exef.exOff + 4);
    exef.exOff += 4;

    return reinterpret_cast<unsigned char*>(fourByteBuf.data());
}

unsigned char* read8Bytes(DOS_Header exef, vector<unsigned char>& buf){

    vector<unsigned char> eightByteBuf(buf.begin() + exef.exOff, buf.begin() + + exef.exOff + 8);
    exef.exOff += 8;

    return reinterpret_cast<unsigned char*>(eightByteBuf.data());
}

unsigned char* read16Bytes(DOS_Header exef, vector<unsigned char>& buf){

    vector<unsigned char> oneSixByteBuf(buf.begin() + exef.exOff, buf.begin() + + exef.exOff + 16);
    exef.exOff += 16;

    return reinterpret_cast<unsigned char*>(oneSixByteBuf.data());
}

unsigned char* read32Bytes(DOS_Header exef, vector<unsigned char>& buf){

    vector<unsigned char> threeTwoByteBuf(buf.begin() + exef.exOff, buf.begin() + + exef.exOff + 32);
    exef.exOff += 32;

    return reinterpret_cast<unsigned char*>(threeTwoByteBuf.data());
}


int readSignature(vector<unsigned char>& buf){

    std::string str(buf.begin(), buf.begin() + 2);
    if(str.compare(exeSig) == 1) return 1;

    return 0;
}

void readDosHeader(vector<unsigned char>& buf, DOS_Header exeh){

    //exeh.lastsize = boost::lexical_cast<short> ();
    std::stringstream ss;

    unsigned char * data = read2Bytes(exeh, buf);

    for(int i=0; i<2; ++i)
        ss << hex << (unsigned int)data[i];
    string mystr = ss.str();

    cout << mystr;
}

int main (int argc, char *argv[])
{
    string path = argv[1];

    ifstream fd(path, ios::in|ios::binary);

    std::istream_iterator<unsigned char> begin(fd), end;
    std::vector<unsigned char> buffer(begin, end);

    if(readSignature(buffer)) { readDosHeader(buffer, exeh); }



    /*std::copy(buffer.begin(),
              buffer.end(),
              std::ostream_iterator<unsigned int>(std::cout << hex, ","));*/

}


