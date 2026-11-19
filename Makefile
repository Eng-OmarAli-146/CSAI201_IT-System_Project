CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra
TARGET   ?= it_system
BUILD    := build

SRC := $(wildcard *.cpp)
OBJ := $(addprefix $(BUILD)/,$(SRC:.cpp=.o))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(TARGET)

.PHONY: all run clean
