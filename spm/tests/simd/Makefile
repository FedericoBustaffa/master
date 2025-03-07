CXX 		= g++
CXXFLAGS	+= -g -Wall -std=c++17 -mavx2 -mfma -march=native
OPTFLAGS	= -O2
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
