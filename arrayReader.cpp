#include "arrayReader.h"

ArrayReader::ArrayReader()
{
	;
}

ArrayReader::ArrayReader(std::vector<uint8_t> &source, uint64_t start_address)
{
	this->array = source;
	this->counter = 0;
	this->start_offset = start_address;
	this->length = this->array.size();
	this->complete = false;
}

uint8_t ArrayReader::read_1byte()
{
	if(this->counter + 1 > this->length)
	{
		this->complete = true;
		return 0;
	}
	uint8_t retVal = this->array[this->counter];
	this->counter++;
	return retVal;
}

uint16_t ArrayReader::read_2byte()
{
	uint16_t retVal;
	if(this->counter + 2 > this->length)
	{
		this->complete = true;
		return 0;
	}
	readLittleEndian(&retVal, (uint8_t *)&this->array[this->counter], 0);
	counter = counter + 2;
	return retVal;
}

int32_t ArrayReader::read_signed_4byte()
{
	int32_t retVal;
	if(this->counter + 4 > this->length)
	{
		this->complete = true;
		return 0;
	}
	readLittleEndian((uint32_t *)&retVal, (uint8_t *)&this->array[this->counter], 0);
	counter = counter + 4;
	return retVal;
}

uint32_t ArrayReader::read_4byte()
{
	uint32_t retVal;
	if(this->counter + 4 > this->length)
	{
		this->complete = true;
		return 0;
	}
	readLittleEndian(&retVal, (uint8_t *)&this->array[this->counter], 0);
	counter = counter + 4;
	return retVal;
}

uint64_t ArrayReader::read_8byte()
{
	uint64_t retVal;
	if(this->counter + 8 > this->length)
	{
		this->complete = true;
		return 0;
	}
	readLittleEndian(&retVal, (uint8_t *)&this->array[this->counter], 0);
	counter = counter + 8;
	return retVal;
}

uint64_t ArrayReader::get_real_offset()
{
	return this->counter + this->start_offset;
}

uint64_t ArrayReader::get_index()
{
	return this->counter;
}

bool ArrayReader::is_complete()
{
	return this->complete;
}
