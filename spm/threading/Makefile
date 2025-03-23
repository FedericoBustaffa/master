CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -O2
LIBS = -pthread
TARGET = threading.out

all: $(TARGET)

threading.out: threading.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

threading.o: threading.cpp
	$(CXX) $(CXXFLAGS) $^ -c

clean:
	-rm *.o *.out

recompile: clean all
