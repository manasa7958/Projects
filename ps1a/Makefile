# Compiler and flags
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lboost_unit_test_framework
INCLUDEDIR = -I. -I./ps1a -I/opt/homebrew/opt/boost/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/

# Your .hpp files
DEPS = ps1a/FibLFSR.hpp
# Your compiled .o files
OBJECTS = ps1a/FibLFSR.o
# Your .a files
LIBRARY = PhotoMagic.a
# Your test program
TEST = test

.PHONY: all clean lint

all: $(LIBRARY) $(TEST)

ps1a/FibLFSR.o: ps1a/FibLFSR.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDEDIR)

test.o: test.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDEDIR)

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

$(TEST): test.o $(OBJECTS) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

clean:
	rm -f *.o ps1a/*.o $(TEST) $(LIBRARY)

lint:
	cpplint *.cpp ps1a/*.hpp
