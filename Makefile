# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall

# Source files
SRC = main.cpp

# Executable name
TARGET = main

# Variables for prob and N
PROB = 1
N = 8

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -DPROB=$(PROB) -DN=$(N) -o $@ $^

clean:
	rm -f $(TARGET)
