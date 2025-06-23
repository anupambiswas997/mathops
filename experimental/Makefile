INCLUDEDIR := .
SRCDIR := .
OBJDIR := .
SRCFILES := $(wildcard $(SRCDIR)/*.cpp)
OBJFILES := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCFILES))
DEPS := $(OBJFILES:.o=.d)

.PHONY: all clean

all: main

main: matrix.o vectr.o main.cpp
	g++ $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -I$(INCLUDEDIR) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf *.o main