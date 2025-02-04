# Compiler and flags
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/opt/boost/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/

# Your .hpp files
DEPS = FibLFSR.hpp
# Your compiled .o files
OBJECTS =  FibLFSR.o
# Your .a files
LIBRARY = PhotoMagic.a
# The name of your program
PROGRAM = PhotoMagic
TEST = test

.PHONY: all clean lint

all: $(PROGRAM) $(TEST) $(LIBRARY)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

$(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

clean:
	rm *.o $(PROGRAM) $(TEST) $(LIBRARY)

lint:
	cpplint *.cpp *.hpp
