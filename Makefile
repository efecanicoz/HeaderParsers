OBJECTS = arrayReader.o elf32.o elf64.o exe32.o exe64.o fileReader.o instruction.o main.o reader.o block.o
OBJDIR = obj
CXXFLAGS = -std=c++11 -g
OBJS = $(patsubst %, $(OBJDIR)/%, $(OBJECTS))
CXX = g++

.PHONY: all
all: file final

file:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

$(OBJDIR)/%.d: %.cpp
	$(CXX) -MM -MT -o $@ $(CXXFLAGS) $<

-include $(DEP)

final: $(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJS)
	
clean:
	-rm final
	-rm -rf $(OBJDIR)
