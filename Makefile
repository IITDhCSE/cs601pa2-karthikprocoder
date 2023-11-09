CXX = g++

EIGEN_PATH = /home/resiliente/cs601software/eigen-3.3.9


# Variables for prob and N
PROB ?= 1
N ?= 2
E := 70
A := 12.5e-4
L := 0.5
P := 5000


CXXFLAGS = -Wall -std=c++11 -DPROB=$(PROB) -DNUM_ELE=$(N)
INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

PROG_NAME = $(BIN_DIR)/FEM

# Default target
run: $(PROG_NAME)
	./$(PROG_NAME) $(E) $(A) $(L) $(P)

compile: $(PROG_NAME)

# Rule to link object files into the executable
$(PROG_NAME): $(OBJ_DIR)/main.o $(OBJ_DIR)/Solution.o $(OBJ_DIR)/Domain.o $(OBJ_DIR)/Element.o 
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile each source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
# Create obj and bin directories if they don't exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: clean
