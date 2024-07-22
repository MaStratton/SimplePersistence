CXX ?= g++

all:
	$(CXX) $(wildcard src/*cpp) -o Run.out -fsanitize=address -ljsoncpp $(shell pkg-config --cflags --libs libmongocxx)
