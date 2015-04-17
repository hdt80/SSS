CXX = g++
CC = gcc

LIBS = -L lib -lglfw3 -lglew32 -lopengl32

SOURCEDIR = code/sources
BUILDDIR = build

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
SOURCES += $(wildcard $(SOURCEDIR)/*/*.cpp)
SOURCES += $(wildcard $(SOURCEDIR)/*/*/*.cpp)

OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

CSOURCES = $(wildcard $(SOURCEDIR)/rendering/*.c)
COBJECTS = $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.o, $(CSOURCES))

CXXFLAGS = -Wall -g -Wno-comment -c -std=c++11 -I include -I code/headers
CFLAGS = -c -I code/headers -I include
LDFLAGS = $(LIBS) lib/stb_image.o

EXE = exe

static: $(OBJECTS) $(COBJECTS)
	$(AR) rvs dist/libengine.a $(addprefix $(BUILDDIR)/, $(notdir $^))
	cp -r ./code/headers/* ./dist

build: $(EXE)

stbi:
	$(CC) -c $(SOURCEDIR)/stb_image.c
	
$(EXE): $(OBJECTS) $(COBJECTS)
		$(CXX) $(addprefix $(BUILDDIR)/, $(notdir $^)) $(LDFLAGS) -o ./bin/$@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
		$(CXX) $(CXXFLAGS) $< -o $(BUILDDIR)/$(notdir $@) 

$(COBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
		$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$(notdir $@)

clean:
	rm $(BUILDDIR)/*.o && rm ./bin/$(EXE)

run:
	./bin/$(EXE)

debug:
	gdb ./bin/$(EXE)
