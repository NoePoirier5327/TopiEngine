CXX = g++
AR = ar
ARFLAGS = rcs
LDFLAGS = -lSDL2
TESTFLAGS = -lgtest -lgtest_main -lpthread
CXXFLAGS = 
CXXFLAGS_BASE = -std=c++17 -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra
BINFLAGS =

LIB = lib/libtopi.a
APP = bin/topi
SRCDIR = src
SRC = $(shell find $(SRCDIR) -name "*.cpp")
OBJDIR = obj
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

# Configuration de tests unitaires avec GTest
TESTDIR = tests
TESTSRC = $(shell find $(TESTDIR) -name "*.cpp")
TESTOBJ = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/$(TESTDIR)/%.o, $(TESTSRC))
TESTAPP = bin/run_tests

# On exclut main.o lors de la liaison des tests
OBJ_NO_MAIN = $(filter-out $(OBJDIR)/main.o, $(OBJ))

.PHONY: all run clean debug doc init lib test release

# Compilation du binaire simple
all: CXXFLAGS = $(CXXFLAGS_BASE)
all: $(APP)

$(APP): $(OBJ)
	@mkdir -p bin
	$(CXX) -o $(APP) $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation du binaire en tant que librairie.
$(LIB): $(OBJ_NO_MAIN)
	@mkdir -p lib
	@mkdir -p include
	cp -rR $(SRCDIR)/topi/ include
	find include -type f -name "*.cpp" -delete
	$(AR) $(ARFLAGS) $@ $^

# Compilation du binaire de test avec GTest
$(TESTAPP): $(OBJ_NO_MAIN) $(TESTOBJ)
	@mkdir -p bin
	$(CXX) -o $@ $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS) $(TESTFLAGS)

$(OBJDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: 
	$(APP)

# Compilation du binaire en tant que librairie prête à être distribuée.
release: CXXFLAGS = $(CXXFLAGS_BASE) -DNDEBUG
release: clean $(LIB)

lib: CXXFLAGS = $(CXXFLAGS_BASE)
lib: clean $(LIB)

test: CXXFLAGS = $(CXXFLAGS_BASE) -g
test: clean $(TESTAPP)
	$(TESTAPP)

clean:
	find $(OBJDIR) -type f -name "*.o" -delete

debug: CXXFLAGS = $(CXXFLAGS_BASE) -g -DDEBUG
debug: clean $(APP)
	gdb $(APP)

doc:
	doxygen Doxyfile

init:
	mkdir -p bin
	mkdir -p obj
