CXX 		= g++
CXXFLAGS	+= -Wall -std=c++17
OPTFLAGS	= -O2
INCLUDES	= -I. -I./include
LIBS		=
SOURCES		= $(wildcard *.cpp)
TARGET		= $(SOURCES:.cpp=)

.PHONY: all clean recompile

%: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(OPTFLAGS) -o $@.x $< $(LIBS)


all: $(TARGET)

clean:
	-rm -rf *.o *~ *.x *.txt

recompile: clean all
