#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <cstdint>
#include <utility>
#include <string>

class Block
{
	public:
		uint64_t start_address; /*Aka name of the node*/
		std::vector<std::pair<uint64_t, std::string>> content;
		uint64_t jump1;
		uint64_t jump2;

		Block();
		~Block();
};

#endif
