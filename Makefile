CXX ?= g++
CXXFLAGS = -fsanitize=address -fpermissive -lhiredis -ljsoncpp

all:
	$(CXX) $(wildcard src/*cpp) -o Run.out $(shell pkg-config --cflags --libs libmongocxx) $(CXXFLAGS)
