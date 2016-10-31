#include "instruction.h"

/*çalışıyor mu emin değilim*/
std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

Instruction::Instruction()
{
	this->done = false;
	this->presence = 0;
	this->legacy_prefix = 0;
}

Instruction::Instruction(ArrayReader *descriptor)
{
	this->desc = descriptor;
	this->done = false;
	this->presence = 0;
	this->legacy_prefix = 0;
	this->rex = 0;
	this->sib = 0;
	this->modrm = 0;
}

Instruction::~Instruction()
{
	;
}

std::string Instruction::get_operand(uint8_t index)
{
	if(index == 1)
		return this->operand1;
	else if(index == 2)
		return this->operand2;
	else if(index == 3)
		return this->operand3;
	else if(index == 4)
		return this->operand4;
	else
		return "";
}

void Instruction::parse_opcode()
{
	std::vector<std::string>split_array = split(this->raw_opcode,' ');
	this->opcode = split_array[0];
	this->operand_count = split_array.size()-1;
	if(split_array.size() == 2)
	{
		this->operand1 = split_array[1];
	}
	else if(split_array.size() == 3)
	{
		this->operand1 = split_array[1];
		this->operand2 = split_array[2];
	}
	else if(split_array.size() == 4)
	{
		this->operand1 = split_array[1];
		this->operand2 = split_array[2];
		this->operand3 = split_array[3];
	}
	else if(split_array.size() == 5)
	{
		this->operand1 = split_array[1];
		this->operand2 = split_array[2];
		this->operand3 = split_array[3];
		this->operand4 = split_array[4];
	}
}

void Instruction::get_operand_value(uint8_t i)
{
	;/*TODO: buraları doldur*/
	std::string *operand;
	std::string rest;
	bool vex,reg,mem,imm,sign;
	vex = reg = mem = imm = sign = false;

	if(i == 1)
		operand = &this->operand1;
	else if(i == 2)
		operand = &this->operand2;
	else if(i == 3)
		operand = &this->operand3;
	else if(i == 4)
		operand = &this->operand4;
	else
		return;

	if(((*operand)[1] >='A' && (*operand)[1] <= 'Z'))
		return;

	switch((*operand)[0])
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
		(*operand) = "rFLAGS";
		return;
	default:
		break;
	}

	switch ((*operand)[0])
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
	rest = (*operand).substr(1);

	if(rest == "a" || rest == "c" || rest == "v" || rest == "y" || rest == "z")
		length = 4;//effective operand size ?
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
			*operand = std::to_string(desc->read_1byte());
		else if(length == 4)
		{
			if(sign == true)
			{
				*operand = std::to_string((int32_t)desc->read_signed_4byte());
			}
			else
			{
				*operand = std::to_string((uint32_t)desc->read_4byte());
			}
		}
	}
	else if(reg == true)
	{
		uint8_t regVal = 0;
		this->read_ModRM();
		if(this->presence & REX)
		{
			regVal = (REX_R(this->rex) << 3) | MODRM_REG(this->modrm);
		}
		else
			regVal = MODRM_REG(this->modrm);
		//operand = register_table

		if(regSel == GPR)
		{
			if(length == 1)
				*operand = modrm_reg_map[0][regVal];
			else if(length == 2)
				*operand = modrm_reg_map[1][regVal];
			else
			{
				if(!REX_W(this->rex))
					*operand = modrm_reg_map[2][regVal];
				else
					*operand = modrm_reg_map[3][regVal];
			}
		}
		else if(regSel == MMX)
		{
			*operand = modrm_reg_map[4][regVal];
		}
		else if(regSel == XMM)
		{
			*operand = modrm_reg_map[5][regVal];
		}
		else if(regSel == YMM)
		{
			*operand = modrm_reg_map[6][regVal];
		}
		else if(regSel == Segment)
		{
			*operand = modrm_reg_map[7][regVal];
		}
		else if(regSel == Control)
		{
			*operand = modrm_reg_map[8][regVal];
		}
		else if(regSel == Debug)
		{
			*operand = modrm_reg_map[9][regVal];
		}
		else
			;//alert
	}
	else if(mem == true)
	{
		std::string result = "";
		uint8_t rm, mod,memVal = 0;
		uint32_t disp;
		this->read_ModRM();
		rm = MODRM_RM(this->modrm);
		mod = MODRM_MOD(this->modrm);

		if(this->presence & REX)
			memVal = (REX_B(this->rex) << 3) | rm;
		else
			memVal = rm;
		memVal |= mod << 4;
		//result = memory_table
		if(mod != 0b00000011)
		{
			if(rm == 0b00000100)
			{
				result = this->read_SIB();
			}

			if(mod == 1)
			{
				disp = this->desc->read_1byte();
			}
			else if(mod == 2)
			{
				disp = this->desc->read_4byte();
			}
			else if(mod == 0 || rm == 0b00000101)
			{
				/*TODO: 64bit ise rip + disp32
				 * diğer modlarda + disp32*/
				disp = this->desc->read_4byte();
			}
			*operand = result + "+" + std::to_string(disp);
		}
		else
		{
			/*TODO:rm de kullanılabilir ?*/
			memVal &= 0x0F;
			if(regSel == GPR)
			{
				if(length == 1)
					*operand = modrm_reg_map[0][memVal];
				else if(length == 2)
					*operand = modrm_reg_map[1][memVal];
				else
				{
					if(!REX_W(this->rex))
						*operand = modrm_reg_map[2][memVal];
					else
						*operand = modrm_reg_map[3][memVal];
				}
			}
			else if(regSel == MMX)
			{
				*operand = modrm_reg_map[4][memVal];
			}
			else if(regSel == XMM)
			{
				*operand = modrm_reg_map[5][memVal];
			}
			else if(regSel == YMM)
			{
				*operand = modrm_reg_map[6][memVal];
			}
			else if(regSel == Segment)
			{
				*operand = modrm_reg_map[7][memVal];
			}
			else if(regSel == Control)
			{
				*operand = modrm_reg_map[8][memVal];
			}
			else if(regSel == Debug)
			{
				*operand = modrm_reg_map[9][memVal];
			}
			else
				;//alert
		}

	}
	else if(vex == true)
	{
		;//bilmiyoz
	}
}

std::string Instruction::read_SIB()
{
	uint8_t base, index;
	std::string result, scale, baseStr;
	if(this->presence & SIB)
	{
		//sib is already read
	}
	else
	{
		this->sib = this->desc->read_1byte();
	}
	this-> presence |= SIB;

	if(this->presence & REX)
	{
		base = REX_B(this->rex) << 3 | SIB_BASE(this->sib);
		index = REX_X(this->rex) << 3 | SIB_INDEX(this->sib);
	}
	else
	{
		base = SIB_BASE(this->sib);
		index = SIB_INDEX(this->sib);
	}
	scale = std::to_string(1 << SIB_SCALE(this->sib));


	if(MODRM_MOD(this->modrm) == 0 && SIB_BASE(this->sib) == 5)
	{
		baseStr = std::to_string(this->desc->read_4byte());
	}
	else
	{
		baseStr = sib_byte_map[SIB_BASE(this->sib)];
	}

	if(index != 0b00000100)
	{
		if(scale != "1")
			result = sib_byte_map[index] + " * " + scale  + " + " + baseStr;
		else
			result = sib_byte_map[index] + scale  + " + " + baseStr;
	}
	else
		result = base;//sadece base
	return result;
}

void Instruction::read_ModRM()
{
	if(this->presence & ModRM)
	{
		//modrm is already read
		return;
	}
	else
	{
		this->modrm = this->desc->read_1byte();
		this->presence |= ModRM;
	}
}

void read_instruction(ArrayReader& descriptor)
{
	const std::string *opcode_map;
	bool read = true;
	uint8_t current_byte;
	uint64_t address;
	Instruction inst;

	inst = Instruction(&descriptor);

	address = descriptor.get_real_offset();
	opcode_map = primary_opcode_map64;

	do
	{
		/*TODO: group olduğu zaman modrmyi nerde okuyacak ? burda değil muhtemelen*/
		if(read)
		{
			current_byte = descriptor.read_1byte();
			inst.raw_opcode = opcode_map[current_byte];
		}
		inst.parse_opcode();

		/*Şimdi bu eşitlik de çalışmaz c++ şov yapar*/
		if(inst.opcode == "ESC")
		{
			read = true;
			if(inst.operand1 == "secondary")
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
		}
		else if(inst.opcode == "PRE")
		{
			read = true;
			if(inst.operand1 == "REX")
			{
				inst.presence |= REX;
				inst.rex = current_byte;
			}
			else if(inst.operand1 == "OSO")
				inst.legacy_prefix |= OSO;
			else if(inst.operand1 == "ASO")
				inst.legacy_prefix |= ASO;
			else if(inst.operand1 == "CS")
				inst.legacy_prefix |= CS;
			else if(inst.operand1 == "DS")
				inst.legacy_prefix |= DS;
			else if(inst.operand1 == "ES")
				inst.legacy_prefix |= ES;
			else if(inst.operand1 == "FS")
				inst.legacy_prefix |= FS;
			else if(inst.operand1 == "GS")
				inst.legacy_prefix |= GS;
			else if(inst.operand1 == "SS")
				inst.legacy_prefix |= SS;
			else if(inst.operand1 == "LOCK")
				inst.legacy_prefix |= LOCK;
			else if(inst.operand1 == "REPE")
				inst.legacy_prefix |= REPE;
			else if(inst.operand1 == "REPNE")
				inst.legacy_prefix |= REPNE;
		}
		else if(inst.opcode == "GROUP")
		{
			uint8_t reg;
			inst.read_ModRM();
			reg = MODRM_REG(inst.modrm);
			read = false;
			if(inst.operand1 == "1")
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
			else if(inst.operand1 == "1a")
			{
				inst.raw_opcode = group1a[reg];
			}
			else if(inst.operand1 == "2")
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
			else if(inst.operand1 == "3")
			{
				if(current_byte == 0xF6)
					inst.raw_opcode = group3_F6[reg];
				else if(current_byte == 0xF7)
					inst.raw_opcode = group3_F7[reg];
			}
			else if(inst.operand1 == "4")
			{
				inst.raw_opcode = group4[reg];
			}
			else if(inst.operand1 == "5")
			{
				inst.raw_opcode = group5[reg];
			}
			else if(inst.operand1 == "6")
			{
				inst.raw_opcode = group6[reg];
			}
			else if(inst.operand1 == "7")
			{
				inst.raw_opcode = group7[reg];
			}
			else if(inst.operand1 == "8")
			{
				inst.raw_opcode = group8[reg];
			}
			else if(inst.operand1 == "9")
			{
				inst.raw_opcode = group9[reg];
			}
			else if(inst.operand1 == "10")
			{
				inst.raw_opcode = group10[reg];
			}
			else if(inst.operand1 == "11")
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
			else if(inst.operand1 == "12")
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
			else if(inst.operand1 == "13")
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
			else if(inst.operand1 == "14")
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
			else if(inst.operand1 == "15")
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
			else if(inst.operand1 == "16")
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
			else if(inst.operand1 == "17")
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
		}
		else
		{
			uint8_t i;
			for(i = 1; i <= inst.operand_count; i++)
			{
				inst.get_operand_value(i);
			}
			inst.done = true;
		}

	}while(inst.done == false);

}

void machine_to_opcode(std::vector<uint8_t> &source, uint64_t start_address)
{
	ArrayReader desc = ArrayReader(source, start_address);
	while(!desc.is_complete())
	{
		read_instruction(desc);
	}
}
