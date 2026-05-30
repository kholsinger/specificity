## Compiler and flags
##
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic

## Directories
##
SRC_DIR  := src
BLD_DIR  := build

## Target executable 
##
TARGET   := $(BLD_DIR)/specificity

## Source and derived object file
##
SRC      := $(SRC_DIR)/specificity.cpp
OBJ      := $(BLD_DIR)/specificity.o

## Default target
##
.PHONY: all
all: $(TARGET)

## Link
##
$(TARGET): $(OBJ) | $(BLD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

## Compile
##
$(OBJ): $(SRC) | $(BLD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

## Create build directory if it doesn't exist
##
$(BLD_DIR):
	mkdir -p $(BLD_DIR)

## Debug build: adds symbols, disables optimization
##
.PHONY: debug
debug: CXXFLAGS += -g -O0 -DDEBUG
debug: $(TARGET)

## Release build: full optimization
##
.PHONY: release
release: CXXFLAGS += -O2 -DNDEBUG
release: $(TARGET)

## Remove build artifacts
##
.PHONY: clean
clean:
	rm -rf $(BLD_DIR)
