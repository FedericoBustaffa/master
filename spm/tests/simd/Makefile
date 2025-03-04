CXX 		= g++
CXXFLAGS	+= -Wall -std=c++17
INCLUDES	= -I. -I./include
LIBS		= #-pthread
SOURCES		= $(wildcard *.cpp)
TARGET		= $(SOURCES:.cpp=)

.PHONY: all clean recompile

%: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -o $@.x $< $(LIBS)


all: $(TARGET)

clean: 
	-rm -rf *.o *~ *.x

recompile: clean all
