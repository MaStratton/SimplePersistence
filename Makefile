CXX ?= g++

all:
	$(CXX) $(wildcard src/*.cpp) -o Run.out -fsanitize=address
