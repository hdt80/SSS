# Compilers
CXX = g++
CC = gcc

CXX_FLAGS = -Wall -c -g -std=c++11 -I include
LINKER_FLAGS = 

# Directories used for input and output
SRCDIR = src
BUILDDIR = build
EXEDIR = bin

OUTPUT_NAME = ArduinoTest

# Where the sources are located
SRCS = $(wildcard $(SRCDIR)/*.cpp)

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