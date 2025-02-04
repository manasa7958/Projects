# Compiler and flags
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I. -I./ps1a -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

# Your .hpp files
DEPS = ps1a/FibLFSR.hpp
# Your compiled .o files
OBJECTS =  ps1a/FibLFSR.o
# Your .a files
LIBRARY = PhotoMagic.a
# The name of your program
PROGRAM = test

.PHONY: all clean lint

all: $(PROGRAM) $(LIBRARY)

ps1a/FibLFSR.o: ps1a/FibLFSR.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDEDIR)

test.o: test.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDEDIR)

$(PROGRAM): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

clean:
	rm -f *.o ps1a/*.o $(PROGRAM) $(LIBRARY)

lint:
	cpplint *.cpp ps1a/*.hpp
