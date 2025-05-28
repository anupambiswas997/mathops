CXX := g++

BUILDDIR := build
OBJDIR := $(BUILDDIR)
SRCDIR := src
INCLUDEDIR := include
SRCFILES := $(wildcard $(SRCDIR)/*.cpp)
OBJFILES := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCFILES))

.PHONY: all clean

all: $(OBJFILES)

show:
	$(info Source-dir: $(SRCDIR))
	$(info Source-files: $(SRCFILES))
	$(info Object-dir: $(OBJDIR))
	$(info Object-files: $(OBJFILES))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -I $(INCLUDEDIR) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(OBJDIR)