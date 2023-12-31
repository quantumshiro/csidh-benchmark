# C++ Compiler
CXX = clang++

# C Compiler
CC = clang

# C++ Compiler Flags
CXXFLAGS = -Wall -Wextra -std=c++17

# C Compiler Flags
CFLAGS = -Wall -Wextra -std=c11

# Include Paths
INCLUDES = -I./src/include

# C++ Source Files
CPPSRC = src/main.cpp
BENCHSRC = src/benchmark.cpp
# C Source Files
CSRC = src/constants.c src/csidh.c src/fp.c src/mont.c src/rng.c src/uint.c

# Object Files
CPPOBJ = $(CPPSRC:.cpp=.o)
COBJ = $(CSRC:.c=.o)
BENCHOBJ = $(BENCHSRC:.cpp=.o)

# Executable Name
EXEC = main
BENCH_EXEC = bench
# Default rule
all: $(EXEC)

# Rule to make the executable
$(EXEC): $(COBJ) $(CPPOBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Rule for C++ object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule for C object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule for benchmark
$(BENCH_EXEC): $(COBJ) $(BENCHOBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -L/usr/lib -lbenchmark -lpthread -o $@ $^
bench: $(BENCH_EXEC)
# Run rule
run: 
	@if [ -f $(EXEC) ]; then \
		./$(EXEC); \
	else \
		$(MAKE) all && ./$(EXEC); \
	fi

# Clean rule
clean:
	rm -f $(COBJ) $(CPPOBJ) $(BENCHOBJ) $(EXEC) $(BENCH_EXEC)

.PHONY: all clean
