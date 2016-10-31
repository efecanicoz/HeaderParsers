#ifndef EXEC_H
#define EXEC_H

class Executable
{
	public:
		virtual std::vector<uint8_t> getSectionContent(std::string) = 0;
		virtual std::vector<std::string> getSectionNames() = 0;
};

#endif
