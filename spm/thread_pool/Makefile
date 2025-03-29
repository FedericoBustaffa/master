CXX = g++
CXXFLAGS = -g -Wall -std=c++17
LIBS = -pthread
OBJ = main.o
TARGET = main.out

all: $(TARGET)

main.out: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

main.o: main.cpp task.hpp task_queue.hpp thread_pool.hpp

clean:
	-rm *.o *.out

recompile: clean all
