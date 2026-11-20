CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra
TARGET   ?= it_system

# plain g++ build: all sources in one command, no extra tooling needed
all: $(TARGET)

$(TARGET): $(wildcard *.cpp) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) $(wildcard *.cpp) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
