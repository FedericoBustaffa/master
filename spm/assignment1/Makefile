CXX 			= g++
CXXFLAGS		= -std=c++17 -fopt-info-vec-missed
OPTFLAGS		= -O3
AUTOFLAGS		= -march=native -ffast-math -funroll-loops
AVXFLAGS		= -march=native -mavx
CXXFLAGS		+= -Wall 
INCLUDES		= -I. -I./include
LIBS			= #-pthread -fopenmp
SOURCES			= $(wildcard *.cpp)
TARGET			= $(SOURCES:.cpp=)

.PHONY: all clean cleanall 

%: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(OPTFLAGS) -o $@.out $< $(LIBS)

# For files with _avx in their name, append flags to CXXFLAGS
%_avx: CXXFLAGS += ${AVXFLAGS}

# For files with _auto in their name, append flags to CXXFLAGS
%_auto: CXXFLAGS += ${AUTOFLAGS}

all: $(TARGET)

clean: 
	-rm -fr *.o *~

cleanall: clean
	-rm -fr *.out
