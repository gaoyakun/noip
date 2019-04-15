CXX?=g++
CXXFLAGS:=-Wall -MMD $(CXXFLAGS)
SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)
TARGETS = $(SRC:%.cpp=%)
DEP = $(SRC:%.cpp=%.d)
DSYM = $(SRC:%.cpp=%.dSYM)

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $@.cpp -o $@

-include $(DEP)

clean:
	-rm -rf $(TARGETS) *.o *.d *.dSYM
