# remove gtests flags for build
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Iinclude -lgtest -lgtest_main

# Source files
SRC = $(wildcard src/*.cpp)

# Test files
TESTS = $(wildcard tests/*.cpp)

# Default target
default: main

main: $(SRC)
	$(CXX) $(CXXFLAGS) -o build/$@ $^

test: $(TESTS)
	$(foreach test,$(TESTS),$(CXX) $(CXXFLAGS) -o build/$(basename $(notdir $(test))) $(test);)
