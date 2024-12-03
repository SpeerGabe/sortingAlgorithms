# Compiler and flags
CC = g++
CFLAGS = -g -Wall -Wextra

# Default target
default: sort

# Rule to create the executable
sort: main.o
	$(CC) $(CFLAGS) -o sort main.o

# Rule to compile the source file into an object file
main.o: sorting.cpp
	$(CC) $(CFLAGS) -c sorting.cpp -o main.o

# Rule to clean up generated files
clean:
	$(RM) sort main.o *~

