CONFIG?=release
CXX?=g++
CXXFLAGS += -Wall -MMD
ifeq ($(CONFIG),release)
  CXXFLAGS += -O3
else
  CXXFLAGS += -g
endif

SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)
TARGETS = $(SRC:%.cpp=%)
DEP = $(SRC:%.cpp=%.d)

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $@.cpp -o $@

-include $(DEP)

clean:
	-rm -rf $(TARGETS) *.o *.d *.dSYM *.exe *.obj
