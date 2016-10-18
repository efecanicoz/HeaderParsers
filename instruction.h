#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstdint>


#ifndef ARRAYREADER_H
	#include "arrayReader.h"
#endif
#include "opcode.h"

enum legacy_prefixes{OSO=0,ASO,CS,DS,ES,FS,GS,SS,LOCK,REPE,REPNE};
enum presence{REX=0, VEX, XOP, ModRM, SIB};

#define MODRM_MOD(modrm) ((modrm & 0xC0) >> 6)
#define MODRM_REG(modrm) ((modrm & 0x38) >> 3)
#define MODRM_RM(modrm)  (modrm & 0x7)

#define SIB_SCALE(sib) ((sib & 0xC0) >> 6)
#define SIB_INDEX(sib) ((sib & 0x38) >> 3)
#define SIB_BASE(sib)  (sib & 0x7)

#define REX_W(rex) ((rex & 0x8) >> 3)
#define REX_R(rex) ((rex & 0x4) >> 2)
#define REX_X(rex) ((rex & 0x2) >> 1)
#define REX_B(rex) (rex & 0x1)

class Instruction
{
	public:
		std::string raw_opcode;
		std::string opcode;
		std::string operand1, operand2, operand3, operand4;
		uint8_t operand_count;
		uint16_t legacy_prefix;
		uint8_t presence;
		uint8_t rex, sib, modrm;
		bool done;
		ArrayReader *desc;

		std::string get_operand(uint8_t);
		void parse_opcode();
		void get_operand_value(uint8_t );
		std::string read_SIB();
		void read_ModRM();
		Instruction();
		Instruction(ArrayReader *);
		~Instruction();

};


void read_instruction();
void machine_to_opcode(std::vector<uint8_t> &, uint64_t );

#ifndef READER
    #include "reader.h"
#endif
/*
extern static const std::string primary_opcode_map32[];
extern static const std::string primary_opcode_map64[];
extern static const std::string secondary_opcode_map_none;
extern static const std::string secondary_opcode_map_66;
extern static const std::string secondary_opcode_map_f2;
extern static const std::string secondary_opcode_map_f3;*/
#endif
