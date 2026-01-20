CXX = g++
CXXFLAGS = -Wall -g

SRC_DIR = src
BIN_DIR = bin

TARGET = $(BIN_DIR)/main

SRCS = $(SRC_DIR)/main.cpp

INC = -Iinclude

all: $(TARGET) run

$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $(SRCS) $(INC) -o $(TARGET)

run: $(TARGET)
	@$(BIN_DIR)/main

clean:
	rm -rf $(BIN_DIR)/*