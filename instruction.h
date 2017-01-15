#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <sstream>
#include <utility>
#include <array>
#include <cstring>
#include "arrayReader.h"
#include "opcode.h"

enum legacy_prefixes{OSO=1,ASO=2,CS=4,DS=8,ES=16,FS=32,GS=64,SS=128,LOCK=256,REPE=512,REPNE=1024};
enum presence{REX=1, VEX=2, XOP=4, ModRM=8, SIB=16};
enum registers{GPR=1,Control=2,Debug=4,YMM=8,XMM=16,MMX=32,Segment=64};

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
        const char * raw_opcode;
		std::string opcode;
        std::array<std::string, 4> operands;
		uint8_t operand_count;
		uint16_t legacy_prefix;
		uint8_t presence;
		uint8_t arch;
		uint8_t rex, sib, modrm, regSel,length;

		bool done;
		ArrayReader *desc;

		std::string get_operand(uint8_t);
        void split_opcode();
		void get_operand_value(uint8_t );
		std::string read_SIB();
        const char *get_x87(uint8_t);
		void read_ModRM();
		Instruction();
		Instruction(ArrayReader *, uint8_t);
		~Instruction();

};


#ifndef READER
    #include "reader.h"
#endif


std::vector<std::string> read_instruction(ArrayReader& , uint8_t );

#endif
