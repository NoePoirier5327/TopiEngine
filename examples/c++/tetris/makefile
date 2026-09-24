CXX = g++
LDDIR = -Llib
LDFLAGS = -ltopi -lSDL2
INCLDDIR = -Iinclude
DEBUGFLAGS = -g
CXXFLAGS = -std=c++17 -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra

APP = bin/tetris
SRCDIR = src
SRC = $(shell find $(SRCDIR) -name "*.cpp")
OBJDIR = obj
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

.PHONY: all run clean debug init

# Compilation du binaire simple
all: $(OBJ)
	@mkdir -p bin
	$(CXX) $(LDDIR) -o $(APP) $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c $(INCLDDIR) $< -o $@

run: 
	$(APP)

clean:
	find $(OBJDIR) -type f -name "*.o" -delete

debug:
	gdb $(APP)

init:
	mkdir -p bin
	mkdir -p obj
