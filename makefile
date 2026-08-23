CXX = g++
LDDIR = 
LDFLAGS = -lSDL2 -lSDL2_image
INCLDDIR = 
DEBUGFLAGS =
CXXFLAGS = -std=c++ -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra
BINFLAGS =

APP = bin/app
SRCDIR = src
SRC = $(shell find $(SRCDIR) -name "*.cpp")
OBJDIR = obj
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

all: $(OBJ)
	$(CXX) $(LDDIR) -o $(APP) $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c $(INCLDDIR) $< -o $@

run: 
	$(APP)

clean:
	rm -r $(OBJDIR)/*.o

doc:
	doxygen Doxyfile

init:
	mkdir -p obj
