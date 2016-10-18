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
	bool vex,reg,mem,imm;
	uint8_t length;
	vex = reg = mem = imm = false;

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
	case 'I':
	case 'J':
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

	rest = (*operand).substr(1);

	if(rest == "a" || rest == "c" || rest == "v" || rest == "y" || rest == "z")
		length = 4;//effective operand size ?
	else if(rest == "b" || rest == "pb" || rest == "ps")
		length = 4;
	else if(rest == "pd" || rest == "pq" || rest == "pqw" || rest == "q")
		length = 8;
	else if(rest == "w" || rest == "ph" || rest == "pi" || rest == "pw")
		length = 2;
	else if(rest == "do")
		length = 32;
	else if(rest == "o")
		length = 16;

	//hangi registerları kullanıyo switch'i ekle
	if(imm == true)
	{
		if(length == 1)
			*operand = std::to_string(desc->read_1byte());
		else if(length == 4)
			*operand = std::to_string(desc->read_4byte());
	}
	else if(reg == true)
	{
		uint8_t regVal = 0;
		if(this->presence & (1 << REX))
		{
			regVal = (REX_R(this->rex) << 3) | reg;
		}
		else
			regVal = reg;
		//operand = register_table
	}
	else if(mem == true)
	{
		std::string result = "";
		uint8_t rm, mod,memVal = 0;
		uint32_t disp;
		this->read_ModRM();
		rm = MODRM_RM(this->modrm);
		mod = MODRM_MOD(this->modrm);

		if(this->presence & (1 << REX))
			memVal = (REX_B(this->rex) << 3) | rm;
		else
			memVal = rm;
		memVal |= mod << 4;
		//result = memory_table
		if(mod != 0b00000011)
		{
			if(rm == 0b00000100)
			{
				//get sib content
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
				disp = this->desc->read_4byte();
			}
		}
		*operand = result + "+" + std::to_string(disp);
	}
	else if(vex == true)
	{
		;//bilmiyoz
	}

}

std::string Instruction::read_SIB()
{
	uint8_t base, index;
	std::string result;
	if(this->presence & (1 << SIB))
	{
		//sib is already read
	}
	else
	{
		this->sib = this->desc->read_1byte();
	}
	this-> presence |= (1 << SIB);
	base = MODRM_MOD(this->modrm) << 3 | SIB_BASE(this->sib);

	if(this->presence & (1 << REX))
		index = REX_X(this->rex) << 3 | SIB_INDEX(this->sib);
	else
		index = SIB_INDEX(this->sib);
	//result = sib_table[index];
	if(index != 0b00000100)
		;//result = result * 1 << SIB_SCALE(this->sib) + base_table[base];
	return result;
}

void Instruction::read_ModRM()
{
	if(this->presence & (1 << ModRM))
	{
		//modrm is already read
		return;
	}
	else
	{
		this->modrm = this->desc->read_1byte();
		this->presence |= (1 << ModRM);
	}
}

void read_instruction(ArrayReader& descriptor)
{
	const std::string *opcode_map;
	uint8_t current_byte;
	uint64_t address;
	Instruction inst;

	inst = Instruction(&descriptor);

	address = descriptor.get_real_offset();
	opcode_map = primary_opcode_map64;

	do
	{
		current_byte = descriptor.read_1byte();
		inst.raw_opcode = opcode_map[current_byte];
		inst.parse_opcode();

		/*Şimdi bu eşitlik de çalışmaz c++ şov yapar*/
		if(inst.opcode == "ESC")
		{
			if(inst.opcode == "secondary")
			{
				if(inst.legacy_prefix & (1 << OSO))
					opcode_map = secondary_opcode_map_66;
				else if(inst.legacy_prefix & (1 << REPE))
					opcode_map = secondary_opcode_map_f2;
				else if(inst.legacy_prefix & (1 << REPNE))
					opcode_map = secondary_opcode_map_f3;
				else
					opcode_map = secondary_opcode_map_none;
			}
		}
		else if(inst.opcode == "PRE")
		{
			if(inst.operand1 == "OSO")
				inst.legacy_prefix |= 1 << OSO;
			else if(inst.operand1 == "ASO")
				inst.legacy_prefix |= 1 << ASO;
			else if(inst.operand1 == "CS")
				inst.legacy_prefix |= 1 << CS;
			else if(inst.operand1 == "DS")
				inst.legacy_prefix |= 1 << DS;
			else if(inst.operand1 == "ES")
				inst.legacy_prefix |= 1 << ES;
			else if(inst.operand1 == "FS")
				inst.legacy_prefix |= 1 << FS;
			else if(inst.operand1 == "GS")
				inst.legacy_prefix |= 1 << GS;
			else if(inst.operand1 == "SS")
				inst.legacy_prefix |= 1 << SS;
			else if(inst.operand1 == "LOCK")
				inst.legacy_prefix |= 1 << LOCK;
			else if(inst.operand1 == "REPE")
				inst.legacy_prefix |= 1 << REPE;
			else if(inst.operand1 == "REPNE")
				inst.legacy_prefix |= 1 << REPNE;
			else if(inst.operand1 == "REX")
			{
				inst.presence |= 1<<REX;
				inst.rex = current_byte;
			}
		}
		else if(inst.opcode == "GROUP")
		{
			/* read modrm after
			 * read new opcode to raw_opcode*/
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
