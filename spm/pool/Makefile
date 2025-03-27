CXX = g++
CXXFLAGS = -g -Wall -std=c++17
LIBS = -pthread
OBJS = main.o
TARGET = pool.out

.PHONY: all clean recompile

all: $(TARGET)

pool.out: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

main.o: main.cpp safe_queue.hpp thread_pool.hpp

clean:
	-rm -rf *.o *.out

recompile: clean all
