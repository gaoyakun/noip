CONFIG?=release
CXX?=g++
CXXFLAGS += -Wall -MMD
ifeq ($(CONFIG),release)
  CXXFLAGS += -O3
else
  CXXFLAGS += -g
endif

SRC = $(wildcard *.cpp)
SRC += $(wildcard core/*.cpp)
OBJ = $(SRC:%.cpp=%.o)
DEP = $(SRC:%.cpp=%.d)

main: $(OBJ)
	$(CXX) $^ -o $@

$(OBJ): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

-include $(DEP)

clean:
	-rm -rf main *.o *.d *.dSYM *.exe *.obj core/*.o core/*.d core/*.dSYM core/*.exe core/*.obj
