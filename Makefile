all:
	g++ -std=c++11 -g instruction.cpp arrayReader.cpp elf32.cpp elf64.cpp main.cpp reader.cpp  -o final

clean:
	rm final