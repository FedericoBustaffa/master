CXX = g++
CXXFLAGS = -g -Wall -std=c++17
LIBS = -pthread
OBJS = main.o thread_pool.o
TARGET = pool.out

.PHONY: all clean recompile

all: $(TARGET)

pool.out: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

main.o: main.cpp safe_queue.hpp
thread_pool.o: thread_pool.hpp thread_pool.cpp

clean:
	-rm -rf *.o *.out

recompile: clean all
