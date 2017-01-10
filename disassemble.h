#ifndef DISASSEMBLE_H
#define DISASSEMBLE_H

#include "instruction.h"
#include <string>
#include <array>
#include <vector>
#include <utility>
#include <map>
#include "block.h"
#include "arrayReader.h"

void disassemble_content(std::vector<std::pair<uint64_t, std::string>> &, std::vector<uint8_t> &source, uint64_t, uint8_t , uint64_t , bool);
void linear_sweep(std::vector<std::pair<uint64_t, std::string>> &, std::vector<uint8_t> &, uint64_t , uint8_t);
void trace_blocks(std::map<uint64_t,Block> &, ArrayReader &, uint8_t , uint64_t );
void recursive_disassemble(std::vector<std::pair<uint64_t, std::string>> &, std::vector<uint8_t> &, uint64_t, uint8_t, uint64_t);

#endif // DISASSEMBLE_H
