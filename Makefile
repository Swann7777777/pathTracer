CXX = g++
CXXFLAGS = -Wall -g -O2

SRC_DIR = src
BIN_DIR = bin

TARGET = $(BIN_DIR)/main
DEBUG_TARGET = $(BIN_DIR)/main-debug

SRCS = $(SRC_DIR)/main.cpp

INC = -Iinclude

all: $(TARGET) run

debug: CXXFLAGS = -Wall -g -O0
debug: $(DEBUG_TARGET) run-debug

$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $(SRCS) $(INC) -o $(TARGET)

$(DEBUG_TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $(SRCS) $(INC) -o $(DEBUG_TARGET)


run: $(TARGET)
	@$(BIN_DIR)/main

run-debug: $(DEBUG_TARGET)
	@$(DEBUG_TARGET)

gdb: $(DEBUG_TARGET)
	gdb ./$(DEBUG_TARGET)

clean:
	rm -rf $(BIN_DIR)/*