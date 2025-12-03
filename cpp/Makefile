CXX=clang++
CXXFLAGS=-std=c++20 -O2 -Iinclude
SRC=$(wildcard src/*cpp)
BIN=$(patsubst src/%.cpp,bin/%,$(SRC))

all: $(BIN)

bin/%: src/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f bin/*
