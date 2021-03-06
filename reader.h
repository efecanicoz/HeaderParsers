#ifndef READER
#define READER

#include <cstdint>

struct e_ident
{
    uint8_t ei_magic[4];
    uint8_t ei_class;
    uint8_t ei_data;
    uint8_t ei_version;
    uint8_t ei_osabi;
    uint8_t ei_abiversion;
    uint8_t ei_pad[7];
};

void readBigEndian(uint8_t*,uint8_t *,int);
void readBigEndian(uint16_t*,uint8_t *,int);
void readBigEndian(uint32_t*,uint8_t *,int);
void readBigEndian(uint64_t*,uint8_t *,int);

void readLittleEndian(uint8_t*,uint8_t *,int);
void readLittleEndian(uint16_t*,uint8_t *,int);
void readLittleEndian(uint32_t*,uint8_t *,int);
void readLittleEndian(uint64_t*,uint8_t *,int);


#endif
