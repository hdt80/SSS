CXX = g++
CC = gcc

LIBS = -L lib -lengine -lglfw3 -lglew32 -lopengl32

SOURCEDIR = code/sources
BUILDDIR = build

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
SOURCES += $(wildcard $(SOURCEDIR)/*/*.cpp)

OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

CSOURCES = $(wildcard $(SOURCEDIR)/rendering/*.c)
COBJECTS = $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.o, $(CSOURCES))

CXXFLAGS = -Wall -Wno-comment -g -c -std=c++11 -I include -I code/headers
CFLAGS = -c -I code/headers -I include
LDFLAGS = $(LIBS) lib/*.o

EXE = app

build: $(EXE)
	
$(EXE): $(OBJECTS) $(COBJECTS)
		$(CXX) $(addprefix $(BUILDDIR)/, $(notdir $^)) $(LDFLAGS) -o ./bin/$@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
		$(CXX) $(CXXFLAGS) $< -o $(BUILDDIR)/$(notdir $@) 

$(COBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
		$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$(notdir $@)
sweep:
	rm $(BUILDDIR)/*.o && rm ./bin/$(EXE)
clean:
	rm $(BUILDDIR)/*.o && rm ./bin/$(EXE)

run:
	./bin/$(EXE)

debug:
	gdb ./bin/$(EXE)
