
.PHONY: all build link
all: build

OBJECTS = arrayReader.o elf32.o elf64.o exe32.o exe64.o fileReader.o instruction.o main.o reader.o 
OBJDIR = obj
BUILDDIR = build
CPPFLAGS = -std=c++11 -g
all: $(OBJECTS)
	


arrayReader.o: arrayReader.cpp arrayReader.h reader.h
	g++ $(CPPFLAGS) -c $^ -o $(OBJDIR)/$@  

elf32.o: elf32.cpp elf32.h reader.h EInterface.h
	g++ $(CPPFLAGS) -c $^ -o $@
	
elf64.o: elf64.cpp elf64.h reader.h EInterface.h
	g++ $(CPPFLAGS) -c $^ -o $@
	
exe32.o: exe32.cpp exe32.h reader.h EInterface.h
	g++ $(CPPFLAGS) -c $^ -o $@
	
exe64.o: exe64.cpp exe64.h reader.h EInterface.h
	g++ $(CPPFLAGS) -c $^ -o $@
	
fileReader.o: fileReader.cpp fileReader.h EInterface.h reader.h elf64.h elf32.h exe32.h exe64.h
	g++ $(CPPFLAGS) -c $^ -o $@
	
instruction.o: instruction.cpp instruction.h arrayReader.h reader.h  opcode.h
	g++ $(CPPFLAGS) -c $^ -o $@
	
main.o: main.cpp
	g++ $(CPPFLAGS) -c $^ -o $@
	
reader.o: reader.cpp reader.h
	g++ $(CPPFLAGS) -c $^ -o $@
	
