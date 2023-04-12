CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./entry/main.cpp ./src/graph.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests: ./entry/tests.cpp ./src/graph.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.DEFAULT_GOAL := exc
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*