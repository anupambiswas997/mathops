CXX := g++

BUILDDIR := build
OBJDIR := $(BUILDDIR)
SRCDIR := src
INCLUDEDIR := include
SRCFILES := $(wildcard $(SRCDIR)/*.cpp)
OBJFILES := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCFILES))
DEPS := $(OBJFILES:.o=.d)
LIB := $(BUILDDIR)/libmathops.a

.PHONY: all clean

all: test $(OBJFILES) $(LIB)

show:
	$(info Source-dir: $(SRCDIR))
	$(info Source-files: $(SRCFILES))
	$(info Object-dir: $(OBJDIR))
	$(info Object-files: $(OBJFILES))
	$(info Deps: $(DEPS))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -I $(INCLUDEDIR) -MMD -MP -c $< -o $@

-include $(DEPS)

test: tests/tests.cpp $(OBJFILES)
	$(CXX) -I $(INCLUDEDIR) $^ -o $@

$(LIB): $(OBJFILES)
	ar rcs $@ $^

clean:
	rm -rf $(BUILDDIR) $(OBJDIR)