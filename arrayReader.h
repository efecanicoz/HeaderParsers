#ifndef ARRAYREADER_H
#define ARRAYREADER_H

#include <cstdint>
#include <vector>

class ArrayReader
{
	public:
		std::vector<uint8_t> array;
		uint64_t counter;
		uint64_t start_offset;
		uint64_t length;
		bool complete;

		ArrayReader();
		ArrayReader(std::vector<uint8_t> &,uint64_t);
		uint8_t read_1byte();
		uint16_t read_2byte();
		uint32_t read_4byte();
		uint64_t read_8byte();
		uint64_t get_real_offset();
		uint64_t get_index();
		bool is_complete();

};


#ifndef READER
    #include "reader.h"
#endif
#endif
