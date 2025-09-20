CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

# Default target
all: examples tests

# Examples
examples: examples/demo examples/source_location_demo

examples/demo: examples/demo.cpp logzy.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

examples/source_location_demo: examples/source_location_demo.cpp logzy.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Tests
tests: tests/basic_test

tests/basic_test: tests/basic_test.cpp logzy.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Run tests
test: tests/basic_test
	./tests/basic_test

# Run examples
run-examples: examples
	@echo "Running demo:"
	./examples/demo
	@echo "\nRunning source location demo:"
	./examples/source_location_demo

# Clean
clean:
	rm -f examples/demo examples/source_location_demo tests/basic_test

.PHONY: all examples tests test run-examples clean