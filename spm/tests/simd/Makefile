CXX 		= g++
CXXFLAGS	+= -Wall -std=c++17 -mavx2 -mfma
OPTFLAGS	= # -O2 -march=native
INCLUDES	= -I. -I./include
LIBS		= #-pthread
SOURCES		= $(wildcard *.cpp)
TARGET		= $(SOURCES:.cpp=)

.PHONY: all clean recompile

%: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(OPTFLAGS) -o $@.x $< $(LIBS)


all: $(TARGET)

clean:
	-rm -rf *.o *~ *.x

recompile: clean all
