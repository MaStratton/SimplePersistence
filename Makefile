CXX ?= g++
CXXFLAGS ?= -fsanitize=address -fpermissive 

all:
	$(CXX) $(wildcard src/*.cpp) -o Run.out  $(shell pkg-config --cflags --libs libmongocxx jsoncpp hiredis) $(CXXFLAGS)
