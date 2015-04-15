# Compilers
CXX = g++
CC = gcc

CXX_FLAGS = -Wall -c -g -std=c++11 -I include -I $(SRCDIR)/include
LINKER_FLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lws2_32

# Directories used for input and output
SRCDIR = src
BUILDDIR = build
EXEDIR = bin

OUTPUT_NAME = 2D_Engine

# Where the sources are located
SRCS = $(wildcard $(SRCDIR)/*.cpp)
SRCS += $(wildcard $(SRCDIR)/network/*.cpp)
SRCS += $(wildcard $(SRCDIR)/power_comps/*.cpp)
SRCS += $(wildcard $(SRCDIR)/render/*.cpp)
SRCS += $(wildcard $(SRCDIR)/util/*.cpp)

# Where the compiled objects are located
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

# Linking all the .o files and with the libs
build: $(OBJS)
	$(CXX) $(addprefix $(BUILDDIR)/, $(notdir $^)) $(LINKER_FLAGS) -o ./bin/$(OUTPUT_NAME)

# Compiling all the .cpp files into .o files
$(OBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXX_FLAGS) $< -o $(BUILDDIR)/$(notdir $@)

# Running the created exe
run:
	./$(EXEDIR)/$(OUTPUT_NAME).exe

debug:
	gdb ./$(EXEDIR)/$(OUTPUT_NAME).exe

# Cleaning everything up
clean:
	rm $(BUILDDIR)/*.o && rm $(EXEDIR)/$(OUTPUT_NAME).exe

# Printing environment vars
print-%:
	@echo $*=($*)