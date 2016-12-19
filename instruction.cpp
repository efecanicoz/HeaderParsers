#include "instruction.h"

Instruction::~Instruction()
{
	;
}

Instruction::Instruction()
{
	this->desc = 0;
	this->arch = 0;
	this->done = false;
	this->presence = 0;
	this->legacy_prefix = 0;
	this->rex = 0;
	this->sib = 0;
	this->modrm = 0;
	this->regSel = 0;
	this->operand_count = 0;
	this->length = 0;
}

Instruction::Instruction(ArrayReader *descriptor, uint8_t arch)
{
	this->desc = descriptor;
	this->arch = arch;
	this->done = false;
	this->presence = 0;
	this->legacy_prefix = 0;
	this->rex = 0;
	this->sib = 0;
	this->modrm = 0;
	this->regSel = 0;
	this->operand_count = 0;
	this->length = 0;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (getline(ss, item, delim))
    {
        tokens.push_back(item);
    }
    return tokens;
}

void Instruction::parse_opcode()
{
	std::vector<std::string>split_array;
	uint8_t i;

	split_array = split(this->raw_opcode,' ');
	this->opcode = split_array[0];
	this->operand_count = split_array.size()-1;

	for(i = 0; i < this->operand_count; i++)
		this->operands[i] = split_array[i+1];
}

void Instruction::get_operand_value(uint8_t i)
{
	std::string &operand = this->operands[i];;
	std::string rest;
	bool vex,reg,mem,imm,sign;
	vex = reg = mem = imm = sign = false;


	if(operand.length() < 2 || ((operand)[1] >='A' && (operand)[1] <= 'Z'))
		return;
	if(operand.length() > 3 && operand.find("mem") != std::string::npos)//x87 operand
	{
		mem = true;
	}
	switch((operand)[0])
	{
	case 'A':
	case 'X':
	case 'Y':
		//bunlar ne
		break;
	case 'B':
	case 'H':
		vex = true;
		break;
	case 'C':
	case 'D':
	case 'G':
	case 'P':
	case 'S':
	case 'V':
		reg = true;
		break;
	case 'E':
	case 'M':
	case 'N':
	case 'Q':
	case 'R':
	case 'U':
	case 'W':
		mem = true;
		break;
	case 'J':
		sign = true;
	case 'I':
	case 'L':
	case 'O':
		imm = true;
		break;
	case 'F':
		(operand) = "rFLAGS";
		return;
	default:
		break;
	}

	switch ((operand)[0])
	{
	case 'E':
	case 'G':
	case 'B':
	case 'R':
		regSel = GPR;//gpr
		break;
	case 'C':
		regSel = Control;
		break;
	case 'D':
		regSel = Debug;
		break;
	case 'H':
	case 'L':
	case 'U':
	case 'V':
	case 'W':
		regSel = YMM | XMM;
		break;
	case 'N':
	case 'P':
	case 'Q':
		regSel = MMX;
		break;
	case 'S':
		regSel = Segment;
	}
	rest = operand.substr(1);

	if(rest == "v")
	{
		if(REX_W(this->rex))
			length = 8;
		else
			length = 4;//effective operand size ?
	}
	else if(rest == "a" || rest == "c" || rest == "y" || rest == "z")
		length = 4;
	else if(rest == "b" )
		length = 1;
	else if(rest == "pb" || rest == "ps")
		length = 4;
	else if(rest == "pd" || rest == "pq" || rest == "pqw" || rest == "q")
		length = 8;
	else if(rest == "w" || rest == "ph" || rest == "pi" || rest == "pw")
		length = 2;
	else if(rest == "do")
		length = 32;
	else if(rest == "o")
		length = 16;


	if(imm == true)
	{
		if(length == 1)
		{
			if(sign == true)
			{
				operand = std::to_string((int32_t)desc->read_signed_1byte());
			}
			else
			{
				operand = std::to_string((uint32_t)desc->read_1byte());
			}
		}
		else if(this->legacy_prefix & OSO)
		{
			if(sign == true)
			{
				operand = std::to_string((int32_t)desc->read_signed_2byte());
			}
			else
			{
				operand = std::to_string((uint32_t)desc->read_2byte());
			}
		}
		else if(length == 4)
		{
			if(sign == true)
			{
				operand = std::to_string((int32_t)desc->read_signed_4byte());
			}
			else
			{
				operand = std::to_string((uint32_t)desc->read_4byte());
			}
		}
		else if(length == 8)
		{
			if(sign == true)
			{
				operand = std::to_string((int32_t)desc->read_signed_8byte());
			}
			else
			{
				operand = std::to_string((uint32_t)desc->read_8byte());
			}
		}
	}
	else if(reg == true)
	{
		uint8_t regVal = 0;
		this->read_ModRM();
		regVal = (REX_R(this->rex) << 3) | MODRM_REG(this->modrm);
		//operand = register_table

		if(regSel & GPR)
		{
			if(length == 1)
				operand = modrm_reg_map[0][regVal];
			else if(length == 2)
				operand = modrm_reg_map[1][regVal];
			else
			{
				if(!REX_W(this->rex))
					operand = modrm_reg_map[2][regVal];
				else
					operand = modrm_reg_map[3][regVal];
			}
		}
		else if(regSel & MMX)
		{
			operand = modrm_reg_map[4][regVal];
		}
		else if(regSel & XMM)
		{
			operand = modrm_reg_map[5][regVal];
		}
		else if(regSel & YMM)
		{
			operand = modrm_reg_map[6][regVal];
		}
		else if(regSel & Segment)
		{
			operand = modrm_reg_map[7][regVal];
		}
		else if(regSel & Control)
		{
			operand = modrm_reg_map[8][regVal];
		}
		else if(regSel & Debug)
		{
			operand = modrm_reg_map[9][regVal];
		}
		else
        {
			;//alert
        }
	}
	else if(mem == true)
	{
		static const std::string modrm_rm_map[64] = this->arch == 0 ? modrm_rm_map_64 : modrm_rm_map_32;
		std::string result = "";
		uint8_t rm, mod,memVal = 0;
		uint32_t disp;

		this->read_ModRM();
		rm = MODRM_RM(this->modrm);
		mod = MODRM_MOD(this->modrm);

		memVal = (REX_B(this->rex) << 3) | rm;
		memVal |= mod << 4;
		//result = memory_table
		if(mod != 0b00000011)
		{
			if(rm == 0b00000100)
			{
				result = this->read_SIB();
			}
			else
			{
				result = modrm_rm_map[memVal];
			}

			if(mod == 1)
			{
				disp = this->desc->read_signed_1byte();
				if((int8_t)disp < 0)
					operand = result + std::to_string((int8_t)disp);
				else
				operand = result + "+" + std::to_string((int8_t)disp);
			}
			else if(mod == 2)
			{
				disp = this->desc->read_signed_4byte();
				if((int32_t)disp < 0)
					operand = result + std::to_string((int32_t)disp);
				else
				operand = result + "+" + std::to_string((int32_t)disp);
			}
			else if(mod == 0 && rm == 0b00000101)
			{
				disp = this->desc->read_signed_4byte();
				if(this->arch == 0)/*64-bit*/
				{
					if((int32_t)disp < 0)
						operand = result + std::to_string((int32_t)disp);
					else
					operand = result + "+" + std::to_string((int32_t)disp);
				}
				else if(this->arch == 1)
					operand = std::to_string((int32_t)disp);
			}
			else
			{
				operand = result;
			}
			operand = "[" + operand + "]";

		}
		else
		{
			/*TODO:rm de kullanılabilir ?*/
			memVal &= 0x0F;
			if(regSel == GPR)
			{
				if(length == 1)
					operand = modrm_reg_map[0][memVal];
				else if(length == 2)
					operand = modrm_reg_map[1][memVal];
				else
				{
					if(!REX_W(this->rex))
						operand = modrm_reg_map[2][memVal];
					else
						operand = modrm_reg_map[3][memVal];
				}
			}
			else if(regSel == MMX)
			{
				operand = modrm_reg_map[4][memVal];
			}
			else if(regSel == XMM)
			{
				operand = modrm_reg_map[5][memVal];
			}
			else if(regSel == YMM)
			{
				operand = modrm_reg_map[6][memVal];
			}
			else if(regSel == Segment)
			{
				operand = modrm_reg_map[7][memVal];
			}
			else if(regSel == Control)
			{
				operand = modrm_reg_map[8][memVal];
			}
			else if(regSel == Debug)
			{
				operand = modrm_reg_map[9][memVal];
			}
			else
            {
				;//alert
            }
		}

	}
	else if(vex == true)
	{
		;//bilmiyoz
	}
}

std::string Instruction::read_SIB()
{
	static const std::string sib_byte_map[16] = this->arch == 0 ? sib_byte_map_64 : sib_byte_map_32;
	uint8_t base, index;
	std::string result, scale, baseStr;


	if(!(this->presence & SIB))//if sib is not read
	{
		this->sib = this->desc->read_1byte();
	}
	this-> presence |= SIB;

	base = REX_B(this->rex) << 3 | SIB_BASE(this->sib);
	index = REX_X(this->rex) << 3 | SIB_INDEX(this->sib);
	scale = std::to_string(1 << SIB_SCALE(this->sib));


    if(MODRM_MOD(this->modrm) == 0 && base == 5)
	{
		baseStr = std::to_string(this->desc->read_4byte());
	}
	else
	{
        baseStr = sib_byte_map[base];
	}

	if(index != 0b00000100)
	{
		if(scale != "1")
			result = sib_byte_map[index] + " * " + scale  + " + " + baseStr;
		else
			result = sib_byte_map[index]  + " + " + baseStr;
	}
	else
		result = baseStr;//sadece base
	return result;
}

void Instruction::read_ModRM()
{
	if(!(this->presence & ModRM))
	{
		this->modrm = this->desc->read_1byte();
		this->presence |= ModRM;
	}
	return;
}

std::string Instruction::get_x87(uint8_t instruction_byte)
{
	uint8_t x87_opcode, x87_modRM;
	this->read_ModRM();
	x87_opcode = instruction_byte - 0xD8; //offset of x87 instructions
	x87_modRM = this->modrm & 0x3F;//get r/m and reg fields of modrm
	if(MODRM_MOD(this->modrm) != 0b11)//0x00-0xBF section
	{
		return x87_low_map[x87_opcode][MODRM_REG(this->modrm)];
	}
	else//0xC0 - 0xFF section
	{
		return x87_high_map[x87_opcode][x87_modRM];
	}
}

std::vector<std::string> read_instruction(ArrayReader& descriptor, uint8_t arch)
{
	const std::string *opcode_map;
	std::vector<std::string> result = std::vector<std::string>();
	bool read = true;
	uint8_t current_byte;
	Instruction inst;

	inst = Instruction(&descriptor, arch);

	if(arch == 0)
		opcode_map = primary_opcode_map64;
	else if(arch == 1)
		opcode_map = primary_opcode_map32;
	else
		return result;//invalid arch

	do
	{
		if(read)
		{
			current_byte = descriptor.read_1byte();
			inst.raw_opcode = opcode_map[current_byte];
			if(inst.raw_opcode == "")
			{
				result.push_back("Invalid");
				return result;
			}
		}

		inst.parse_opcode();

		if(inst.opcode == "ESC")
		{
			read = true;
			if(inst.operands[0] == "secondary")
			{
				if(inst.legacy_prefix & OSO)
					opcode_map = secondary_opcode_map_66;
				else if(inst.legacy_prefix & REPE)
					opcode_map = secondary_opcode_map_f2;
				else if(inst.legacy_prefix & REPNE)
					opcode_map = secondary_opcode_map_f3;
				else
					opcode_map = secondary_opcode_map_none;
			}
			else if(inst.operands[0] == "x87")
			{
				inst.raw_opcode = inst.get_x87(current_byte);
				if(inst.raw_opcode == "")
				{
					result.push_back("Invalid");
					return result;
				}
				read = false;
			}
		}
		else if(inst.opcode == "PRE")
		{
			read = true;
			if(inst.operands[0] == "REX")
			{
				inst.presence |= REX;
				inst.rex = current_byte;
			}
			else if(inst.operands[0] == "OSO")
				inst.legacy_prefix |= OSO;
			else if(inst.operands[0] == "ASO")
				inst.legacy_prefix |= ASO;
			else if(inst.operands[0] == "CS")
				inst.legacy_prefix |= CS;
			else if(inst.operands[0] == "DS")
				inst.legacy_prefix |= DS;
			else if(inst.operands[0] == "ES")
				inst.legacy_prefix |= ES;
			else if(inst.operands[0] == "FS")
				inst.legacy_prefix |= FS;
			else if(inst.operands[0] == "GS")
				inst.legacy_prefix |= GS;
			else if(inst.operands[0] == "SS")
				inst.legacy_prefix |= SS;
			else if(inst.operands[0] == "LOCK")
				inst.legacy_prefix |= LOCK;
			else if(inst.operands[0] == "REPE")
				inst.legacy_prefix |= REPE;
			else if(inst.operands[0] == "REPNE")
				inst.legacy_prefix |= REPNE;
		}
		else if(inst.opcode == "GROUP")
		{
			uint8_t reg;
			inst.read_ModRM();
			reg = MODRM_REG(inst.modrm);
			read = false;
			if(inst.operands[0] == "1")
			{
				if(current_byte == 0x80)
				{
					inst.raw_opcode = group1_80[reg];
				}
				else if(current_byte == 0x81)
				{
					inst.raw_opcode = group1_81[reg];
				}
				else if(current_byte == 0x82)
				{
					inst.raw_opcode = group1_82[reg];
				}
				else if(current_byte == 0x83)
				{
					inst.raw_opcode = group1_83[reg];
				}
				else
				{
					;//error
				}
			}
			else if(inst.operands[0] == "1a")
			{
				inst.raw_opcode = group1a[reg];
			}
			else if(inst.operands[0] == "2")
			{
				if(current_byte == 0xC0)
				{
					inst.raw_opcode = group2_C0[reg];
				}
				else if(current_byte == 0xC1)
				{
					inst.raw_opcode = group2_C1[reg];
				}
				else if(current_byte == 0xD0)
				{
					inst.raw_opcode = group2_D0[reg];
				}
				else if(current_byte == 0xD1)
				{
					inst.raw_opcode = group2_D1[reg];
				}
				else if(current_byte == 0xD2)
				{
					inst.raw_opcode = group2_D2[reg];
				}
				else if(current_byte == 0xD3)
				{
					inst.raw_opcode = group2_D3[reg];
				}
				else
				{
					;//error
				}
			}
			else if(inst.operands[0] == "3")
			{
				if(current_byte == 0xF6)
					inst.raw_opcode = group3_F6[reg];
				else if(current_byte == 0xF7)
					inst.raw_opcode = group3_F7[reg];
			}
			else if(inst.operands[0] == "4")
			{
				inst.raw_opcode = group4[reg];
			}
			else if(inst.operands[0] == "5")
			{
				inst.raw_opcode = group5[reg];
			}
			else if(inst.operands[0] == "6")
			{
				inst.raw_opcode = group6[reg];
			}
			else if(inst.operands[0] == "7")
			{
				inst.raw_opcode = group7[reg];
			}
			else if(inst.operands[0] == "8")
			{
				inst.raw_opcode = group8[reg];
			}
			else if(inst.operands[0] == "9")
			{
				inst.raw_opcode = group9[reg];
			}
			else if(inst.operands[0] == "10")
			{
				inst.raw_opcode = group10[reg];
			}
			else if(inst.operands[0] == "11")
			{
				if(current_byte == 0xC6)
				{
					inst.raw_opcode = group11_C6[reg];
				}
				else if(current_byte == 0xC7)
				{
					inst.raw_opcode = group11_C7[reg];
				}
			}
			else if(inst.operands[0] == "12")
			{
				if(inst.legacy_prefix & OSO)
					inst.raw_opcode = group12[1][reg];
				else if(inst.legacy_prefix & REPNE)
					inst.raw_opcode = group12[2][reg];
				else if(inst.legacy_prefix & REPE)
					inst.raw_opcode = group12[3][reg];
				else//none
					inst.raw_opcode = group12[0][reg];
			}
			else if(inst.operands[0] == "13")
			{
				if(inst.legacy_prefix & OSO)
					inst.raw_opcode = group13[1][reg];
				else if(inst.legacy_prefix & REPNE)
					inst.raw_opcode = group13[2][reg];
				else if(inst.legacy_prefix & REPE)
					inst.raw_opcode = group13[3][reg];
				else//none
					inst.raw_opcode = group13[0][reg];
			}
			else if(inst.operands[0] == "14")
			{
				if(inst.legacy_prefix & OSO)
					inst.raw_opcode = group14[1][reg];
				else if(inst.legacy_prefix & REPNE)
					inst.raw_opcode = group14[2][reg];
				else if(inst.legacy_prefix & REPE)
					inst.raw_opcode = group14[3][reg];
				else//none
					inst.raw_opcode = group14[0][reg];
			}
			else if(inst.operands[0] == "15")
			{
				if(inst.legacy_prefix & OSO)
					inst.raw_opcode = group15[1][reg];
				else if(inst.legacy_prefix & REPNE)
					inst.raw_opcode = group15[2][reg];
				else if(inst.legacy_prefix & REPE)
					inst.raw_opcode = group15[3][reg];
				else//none
					inst.raw_opcode = group15[0][reg];
			}
			else if(inst.operands[0] == "16")
			{
				if(inst.legacy_prefix & OSO)
					inst.raw_opcode = group16[1][reg];
				else if(inst.legacy_prefix & REPNE)
					inst.raw_opcode = group16[2][reg];
				else if(inst.legacy_prefix & REPE)
					inst.raw_opcode = group16[3][reg];
				else//none
					inst.raw_opcode = group16[0][reg];
			}
			else if(inst.operands[0] == "17")
			{
				if(inst.legacy_prefix & OSO)
					inst.raw_opcode = group17[1][reg];
				else if(inst.legacy_prefix & REPNE)
					inst.raw_opcode = group17[2][reg];
				else if(inst.legacy_prefix & REPE)
					inst.raw_opcode = group17[3][reg];
				else//none
					inst.raw_opcode = group17[0][reg];
			}
			else
			{
				;//error
			}

			/*Instruction is invalid and read 1 more byte than it should*/
			if(inst.raw_opcode == "")
			{
				printf("Invalid, sync lost.");
				//return "";
			}
		}
		else
		{
			uint8_t i;
			result.push_back(inst.opcode);
			for(i = 0; i < inst.operand_count; i++)
			{
				inst.get_operand_value(i);
				result.push_back(inst.operands[i]);
			}
			inst.done = true;
		}

	}while(inst.done == false);
    return result;
}

void machine_to_opcode(std::vector<std::pair<uint64_t, std::string>> &container, std::vector<uint8_t> &source,
			uint64_t start_address, uint8_t arch)
{
	ArrayReader desc = ArrayReader(source, start_address);
	uint64_t ip;
	std::vector<std::string>inst;
    std::string instruction;
	while(!desc.is_complete())
	{
        instruction = "";
		ip = desc.get_real_offset();
		inst = read_instruction(desc, arch);
		for(std::string str : inst)
		{
			instruction += str + " ";
		}

		/*printf("%llx\t: %s\n",ip,inst.c_str());*/
		container.push_back(std::make_pair(ip, instruction));
	}
	return;
}

std::map<uint64_t, Block> recursive_disassemble(std::vector<uint8_t> &source, uint64_t start_address, uint8_t arch, uint64_t offset)
{
	std::map<uint64_t, Block> block_table = std::map<uint64_t, Block>();
	ArrayReader desc = ArrayReader(source, start_address);
	machine_to_opcode2(block_table, desc, arch, offset);
	return block_table;
}

void machine_to_opcode2(std::map<uint64_t, Block> &table, ArrayReader &desc, uint8_t arch, uint64_t offset)
{
	std::vector<std::pair<uint64_t, std::string>> container = std::vector<std::pair<uint64_t, std::string>>();
    uint64_t ip;
	std::string inst;
	std::vector<std::string> instruction;
	Block current_block;
	current_block.start_address = offset;
	desc.counter = offset;

	/*Bazı bloklar birden fazla kez oluşturuluyor, akış sırasında var olup olmadığını bilmiyoruz*/
	while(!desc.is_complete())
	{
		inst = "";
		ip = desc.get_real_offset();
		instruction = read_instruction(desc, arch);
		for(std::string str : instruction)
		{
			inst += str + " ";
		}
		container.push_back(std::make_pair(ip, inst));

		if(instruction[0].compare("CALL") == 0)
		{
			/*if operand is non numeric*/
			if((instruction[1][0] < '0' || instruction[1][0] > '9') && instruction[1][0] != '-')
			{
				continue;
			}
			current_block.jump1 = desc.counter + std::stoi(instruction[1],nullptr);
			current_block.jump2 = desc.counter;
			break;
		}
		else if(instruction[0].compare("JMP") == 0)
		{
			if((instruction[1][0] < '0' || instruction[1][0] > '9') && instruction[1][0] != '-')
			{
				break;
			}
			current_block.jump1 = desc.counter + std::stoi(instruction[1],nullptr);
			break;
		}
		else if(instruction[0].find("J") == 0)
		{
			/*conditional jump*/
			current_block.jump1 = desc.counter + std::stoi(instruction[1],nullptr);
			current_block.jump2 = desc.counter;
			break;
		}
		else if(instruction[0].compare("RET") == 0)
		{
			break;
		}
	}
	/*add this block to the global table*/
	current_block.content = container;
	table[current_block.start_address] = current_block;
	if(current_block.jump1 != 0 && desc.within_array(current_block.jump1) && table.count(current_block.jump1) == 0)
	{
        printf("here: %lx jumping to(1): %lx\n", (ip+0xe015fb-1024), (current_block.jump1+0xe015fb));
		machine_to_opcode2(table, desc, arch, current_block.jump1);

	}
	if(current_block.jump2 != 0 && desc.within_array(current_block.jump2) && table.count(current_block.jump2) == 0)
	{
        printf("here: %lx jumping to(2): %lx\n", (ip+0xe015fb-1024), (current_block.jump2+0xe015fb));
		return machine_to_opcode2(table, desc, arch, current_block.jump2);

	}
	return;
}


