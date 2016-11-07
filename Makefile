all:
	g++ -std=c++11 -g instruction.cpp arrayReader.cpp elf32.cpp elf64.cpp exe32.cpp exe64.cpp main.cpp reader.cpp fileReader.cpp -o final

clean:
	rm final
