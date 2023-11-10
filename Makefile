CXX = g++

EIGEN_PATH = /home/resiliente/cs601software/eigen-3.3.9


# Variables for prob and N
PROB ?= 1
N ?= 2
E := 70e9
A := 12.5e-4
L := 0.5
P := 5000

# run 70 12.5e-4 0.5 5000

CXXFLAGS = -Wall -g -std=c++17 -DPROB=$(PROB) -DNUM_ELE=$(N)
INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

PROG_NAME = $(BIN_DIR)/FEM

# Default target
run: clean $(PROG_NAME)
	./$(PROG_NAME) $(E) $(A) $(L) $(P)

$(PROG_NAME): $(OBJ_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/Solution.h $(INC_DIR)/Domain.h $(INC_DIR)/Element.h 
	$(CXX) $(CXXFLAGS) -I $(INC_DIR)/ -I $(EIGEN_PATH) -c $< -o $@
	
# Create obj and bin directories if they don't exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

team:
	@echo Team Members:
	@echo 210010015 - Divy Jain
	@echo 210010022 - Karthik Hegde

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

.PHONY: clean
