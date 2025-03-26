CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2
LIBS = -pthread
OBJS = main.o thread_pool.o
TARGET = run.out

.PHONY: all clean recompile

all: $(TARGET)

run.out: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

main.o: main.cpp
thread_pool.o: thread_pool.hpp thread_pool.cpp

clean:
	-rm -rf *.o *.out

recompile: clean all
