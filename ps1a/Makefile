# Compiler and flags
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lboost_unit_test_framework
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/

# Your .hpp files
DEPS = FibLFSR.hpp
# Your compiled .o files
OBJECTS = FibLFSR.o
# Your .a files
LIBRARY = PhotoMagic.a
# Your test program
TEST = test

.PHONY: all clean lint

all: $(LIBRARY) $(TEST)

FibLFSR.o: FibLFSR.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDEDIR)

test.o: test.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDEDIR)

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

$(TEST): test.o $(OBJECTS) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

clean:
	rm -f *.o $(TEST) $(LIBRARY)

lint:
	cpplint *.cpp *.hpp
