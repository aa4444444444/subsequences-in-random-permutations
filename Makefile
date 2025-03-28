# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Target executable
TARGET = main

# For deleting the target
TARGET_DEL = main.exe

# Source files
define SRCS 
source/main.cpp source/schensted.cpp source/permutation.cpp
endef

# Header only files that we depend on
define DEPS
endef

# Object files
OBJS = $(SRCS:.cpp=.o)

# This determines how to handle make clean
# Differentiates between windows vs linux systems
ifdef OS
   RM = del /Q
   FixPath = $(subst /,\,$1)
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      FixPath = $1
   endif
endif

# Default rule to build and run the executable
all: $(TARGET)

# Rule to link object files into the target executable
$(TARGET): $(OBJS) $(call FixPath, $(DEPS))
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run: $(TARGET)
	$(TARGET)

# Clean rule to remove generated files
clean:
	$(RM) $(call FixPath, $(TARGET_DEL)) $(call FixPath, $(OBJS))