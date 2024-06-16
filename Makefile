# /*
#  * Author: Hadar Froimowich.
#  * ID: 213118458
#  * Email: hadarfro12@gmail.com
#  */

CXX = clang++
CXXFLAGS = -std=c++11 -g -O0 -Werror -Wsign-conversion
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Define all source files
SOURCES = Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp Demo.cpp
# Define object files (automatically replace .cpp with .o)
OBJECTS = $(SOURCES:.cpp=.o)

# Define executables
EXECS = Demo test

# Default target to build all executables
all: $(EXECS)

# Build the Demo executable
Demo: Demo.o $(filter-out TestCounter.o Test.o Demo.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build the test executable
test: TestCounter.o Test.o $(filter-out Demo.o TestCounter.o Test.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run clang-tidy on the source files
tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

# Run valgrind to check for memory leaks
valgrind: $(EXECS)
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./Demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean build artifacts
clean:
	rm -f *.o $(EXECS)
