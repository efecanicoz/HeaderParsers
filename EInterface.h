#ifndef EXEC_H
#define EXEC_H

#include <vector>
#include <string>

class ExecutableFile
{
	public:
        virtual std::vector<uint8_t> getHexSectionContent(std::string) = 0;
		virtual std::vector<std::string> getSectionNames() = 0;
        virtual void disassemble(std::vector<std::pair<uint64_t, std::string > > &) = 0;
        virtual std::string getHeaderInfo() = 0;
        virtual std::vector<uint8_t> getHexHeader() = 0;
        virtual std::string getSectionContent(std::string, bool) = 0;

};

#endif
