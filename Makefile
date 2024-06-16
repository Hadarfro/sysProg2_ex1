# /*
#  * Author: Hadar Froimowich.
#  * ID: 213118458
#  * Email: hadarfro12@gmail.com
#  */

CXX = clang++
CXXFLAGS = -std=c++11 -g -O0 -Werror -Wsign-conversion
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target to run the executables
run: demo test
	./demo 
	./test

# Build the demo executable
demo: Demo.o $(filter-out TestCounter.o Test.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build the test executable
test: TestCounter.o Test.o $(filter-out Demo.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run clang-tidy on the source files
tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

# Run valgrind to check for memory leaks
valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean build artifacts
clean:
	rm -f *.o demo test
