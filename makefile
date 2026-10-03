CXX = g++
AR = ar
ARFLAGS = rcs
LDFLAGS = -lSDL2 -lSDL2_ttf
TESTFLAGS = -lgtest -lgtest_main -lpthread
CXXFLAGS = -std=c++17 -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra
INCLUDE_DIR = 
BINFLAGS =

CXXLIB = lib/libtopi.a
LUALIB = lua/topi.so
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
OBJ_LUA_LIB = $(filter-out $(OBJDIR)/main.o, $(OBJ))
OBJ_WITHOUT_LUA = $(filter-out $(OBJDIR)/lua.o, $(OBJ))
OBJ_CXX_LIB = $(filter-out $(OBJDIR)/main.o $(OBJDIR)/lua.o, $(OBJ))

.PHONY: all run clean debug doc init lib test release

# Compilation du binaire simple
all: $(APP)

$(APP): $(OBJ_WITHOUT_LUA)
	@mkdir -p bin
	$(CXX) -o $(APP) $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE_DIR) $< -o $@

# Compilation du binaire en tant que librairie.
$(CXXLIB): $(OBJ_CXX_LIB)
	@mkdir -p lib
	@mkdir -p include
	cp -rR $(SRCDIR)/topi/ include
	find include -type f -name "*.cpp" -delete
	$(AR) $(ARFLAGS) $@ $^

$(LUALIB): $(OBJ_LUA_LIB)
	@mkdir -p lua
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compilation du binaire de test avec GTest
$(TESTAPP): $(OBJ_NO_MAIN) $(TESTOBJ)
	@mkdir -p bin
	$(CXX) -o $@ $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS) $(TESTFLAGS)

$(OBJDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: 
	$(APP)

lib: CXXFLAGS += -DNDEBUG
lib: clean $(CXXLIB)

lua: INCLUDE_DIR += -I/usr/include/lua5.4
lua: LDFLAGS += -shared -llua5.4
lua: CXXFLAGS += -DNDEBUG -fPIC
lua: clean $(LUALIB)

test: CXXFLAGS += -g
test: clean $(TESTAPP)
	$(TESTAPP)

clean:
	find $(OBJDIR) -type f -name "*.o" -delete

debug: CXXFLAGS += -g -DDEBUG
debug: clean $(APP)
	gdb $(APP)

doc:
	doxygen Doxyfile

init:
	mkdir -p bin
	mkdir -p obj
