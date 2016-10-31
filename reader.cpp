#include "reader.h"

void readBigEndian(uint8_t *to, uint8_t from[], int offset)
{
    *to = from[offset];
}

void readBigEndian(uint16_t *to, uint8_t from[], int offset)
{
    *to = from[offset]<<8 
        |from[offset+1];
}

void readBigEndian(uint32_t *to, uint8_t from[], int offset)
{
    *to = from[offset]<<24
        |from[offset+1]<<16
        |from[offset+2]<<8
        |from[offset+3];
}

void readBigEndian(uint64_t *to, uint8_t from[], int offset)
{
    *to = (static_cast<uint64_t>(from[offset]) << 56) |
        (static_cast<uint64_t>(from[offset+1]) << 48) |
        (static_cast<uint64_t>(from[offset+2]) << 40) |
        (static_cast<uint64_t>(from[offset+3]) << 32) |
        (static_cast<uint64_t>(from[offset+4]) << 24) |
        (static_cast<uint64_t>(from[offset+5]) << 16) |
        (static_cast<uint64_t>(from[offset+6]) <<  8) |
        (static_cast<uint64_t>(from[offset+7])) ; 
}

void readLittleEndian(uint8_t *to, uint8_t from[], int offset)
{
    *to = from[offset];
}
void readLittleEndian(uint16_t *to, uint8_t from[], int offset)
{
    *to = from[offset] 
        |from[offset+1]<<8;
}
void readLittleEndian(uint32_t *to, uint8_t from[], int offset)
{
    *to = from[offset]
        |from[offset+1]<<8
        |from[offset+2]<<16
        |from[offset+3]<<24;
}
void readLittleEndian(uint64_t *to, uint8_t from[], int offset)
{
    *to = (static_cast<uint64_t>(from[offset]) <<  0) |
        (static_cast<uint64_t>(from[offset+1]) <<  8) |
        (static_cast<uint64_t>(from[offset+2]) << 16) |
        (static_cast<uint64_t>(from[offset+3]) << 24) |
        (static_cast<uint64_t>(from[offset+4]) << 32) |
        (static_cast<uint64_t>(from[offset+5]) << 40) |
        (static_cast<uint64_t>(from[offset+6]) << 48) |
        (static_cast<uint64_t>(from[offset+7]) << 56) ; 
}

