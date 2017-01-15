#include "disassemble.h"

void linear_sweep(std::vector<std::pair<uint64_t, std::string>> &container, std::vector<uint8_t> &source,
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
        container.push_back(std::make_pair(ip, instruction));
    }
    return;
}

void disassemble_content(std::vector<std::pair<uint64_t, std::string>> &container, std::vector<uint8_t> &source, uint64_t start_address,
                                                          uint8_t arch, uint64_t offset = 0, bool linearSweep = true)
{
    if(true == linearSweep)
    {
        linear_sweep(container, source, start_address, arch);
    }
    else
    {
        recursive_disassemble(container, source, start_address, arch, offset);
    }
}

void recursive_disassemble(std::vector<std::pair<uint64_t, std::string>> &inst_container, std::vector<uint8_t> &source, uint64_t start_address,
                                                                    uint8_t arch, uint64_t offset)
{
    std::map<uint64_t, Block> block_table = std::map<uint64_t, Block>();
    ArrayReader desc = ArrayReader(source, start_address);
    trace_blocks(block_table, desc, arch, offset);
    /*convert to vector*/
    for(auto &kv : block_table)
    {
        for(auto &line : kv.second.content)
        {
            inst_container.push_back(std::make_pair(line.first, line.second));
        }
    }
    return ;
}

std::map<uint64_t, Block> get_blocks(std::vector<uint8_t> &source, uint64_t start_address,
                                                                    uint8_t arch, uint64_t offset)
{
    std::map<uint64_t, Block> block_table = std::map<uint64_t, Block>();
    ArrayReader desc = ArrayReader(source, start_address);
    trace_blocks(block_table, desc, arch, offset);

    return block_table;
}

void trace_blocks(std::map<uint64_t, Block> &table, ArrayReader &desc, uint8_t arch, uint64_t offset)
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
        trace_blocks(table, desc, arch, current_block.jump1);

    }
    if(current_block.jump2 != 0 && desc.within_array(current_block.jump2) && table.count(current_block.jump2) == 0)
    {
        return trace_blocks(table, desc, arch, current_block.jump2);

    }
    return;
}
