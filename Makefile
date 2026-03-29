########################## Compiler ############################

CXX = g++
CXXFLAGS = -fPIC -Wall -g -O2 -pthread
SHARED_FLAGS = -shared

########################## Target ############################

TUI_SRC := src/TuiController.cc src/Window.cc
TUI_OBJ := $(TUI_SRC:.cc=.o)
TUI_LIB := libTui.so

UTILS_SRC := src/Utils.cc
UTILS_OBJ := $(UTILS_SRC:.cc=.o)
UTILS_LIB := libUtils.so

ALL_LIB := $(TUI_LIB) $(UTILS_LIB)
LDLIBS := $(patsubst lib%.so, -l%, $(ALL_LIB))

EXE := LazyGDB
MAIN_SRC := src/main.cc
MAIN_OBJ := $(MAIN_SRC:.cc=.o)

########################## Build ############################

all: $(EXE)

$(EXE): $(MAIN_OBJ) $(ALL_LIB)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(MAIN_OBJ) -L. $(LDLIBS)
$(TUI_LIB): $(TUI_OBJ)
	$(CXX) $(CXXFLAGS) $(SHARED_FLAGS) -o $@ $^
$(UTILS_LIB): $(UTILS_OBJ)
	$(CXX) $(CXXFLAGS) $(SHARED_FLAGS) -o $@ $^
src/%.o: src/%.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f $(EXE)
	rm -f $(ALL_LIB)
	rm -f src/*.o

########################## PHONY ############################

.PHONY: all clean
