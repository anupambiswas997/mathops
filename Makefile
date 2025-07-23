CXX := g++

BUILDDIR := build
OBJDIR := $(BUILDDIR)
INCLUDEDIR := include
# Source directories - these will pertain to the different math modules
SRCDIR1 := src/calculus
SRCDIR2 := src/linear_algebra
SRCDIR3 := src/utils

SRCFILES1 := $(wildcard $(SRCDIR1)/*.cpp)
SRCFILES2 := $(wildcard $(SRCDIR2)/*.cpp)
SRCFILES3 := $(wildcard $(SRCDIR3)/*.cpp)

OBJFILES1 := $(patsubst $(SRCDIR1)/%.cpp, $(OBJDIR)/%.o, $(SRCFILES1))
OBJFILES2 := $(patsubst $(SRCDIR2)/%.cpp, $(OBJDIR)/%.o, $(SRCFILES2))
OBJFILES3 := $(patsubst $(SRCDIR3)/%.cpp, $(OBJDIR)/%.o, $(SRCFILES3))

OBJFILES := $(OBJFILES1) $(OBJFILES2) $(OBJFILES3)
DEPS := $(OBJFILES:.o=.d)
LIB := $(BUILDDIR)/libmathops.a
TESTSDIR := tests
TEST := $(TESTSDIR)/test
TEST_HEADERS := $(TESTSDIR)/linear_algebra_tests.hpp

.PHONY: all clean test

all: $(TEST) $(OBJFILES) $(LIB)

show:
	$(info Source-dirs: $(SRCDIR1) $(SRCDIR2) $(SRCDIR3))
	$(info Source-files: $(SRCFILES1) $(SRCFILES2) $(SRCFILES3))
	$(info Object-dir: $(OBJDIR))
	$(info Object-files: $(OBJFILES))
	$(info Deps: $(DEPS))

define BUILD_MODULE
$(1)/%.o: $(2)/%.cpp
	@mkdir -p $(1)
	$(CXX) -I$(INCLUDEDIR) -MMD -MP -c $$< -o $$@
endef

$(eval $(call BUILD_MODULE, $(OBJDIR), $(SRCDIR1)))
$(eval $(call BUILD_MODULE, $(OBJDIR), $(SRCDIR2)))
$(eval $(call BUILD_MODULE, $(OBJDIR), $(SRCDIR3)))

-include $(DEPS)

$(TEST): tests/tests.cpp $(TEST_HEADERS) $(OBJFILES)
	$(CXX) -I $(INCLUDEDIR) $^ -o $@

$(LIB): $(OBJFILES)
	ar rcs $@ $^

clean:
	rm -rf $(BUILDDIR) $(OBJDIR)

test: $(TEST)
	./$(TEST)