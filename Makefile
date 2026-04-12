########################## Compiler ############################

CXX = g++
CXXFLAGS = -fPIC -Wall -O2 -pthread --std=c++20
CXXFLAGS += $(shell Ulogger-config --cflags)
LIBS = 
LIBS += $(shell Ulogger-config --libs)

########################## Target ############################

SRC := $(wildcard src/*.cc)
OBJ := $(SRC:.cc=.o)
EXE := LazyGDB

########################## Build ############################

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)
src/%.o: src/%.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f $(EXE)
	rm -f $(OBJ)

########################## PHONY ############################

.PHONY: all clean
