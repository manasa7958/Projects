# Compiler and flags
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/

# Your .hpp files
DEPS = FibLFSR.hpp
# Your compiled .o files
OBJECTS = FibLFSR.o
# The name of your program
PROGRAM = PhotoMagic
TEST = test

.PHONY: all clean lint

all: $(PROGRAM) $(TEST) PhotoMagic.a

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $<

$(PROGRAM): test.o $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDEDIR) $(LIBDIR) -o $@ $^ $(LIB)

$(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDEDIR) $(LIBDIR) -o $@ $^ $(LIB)

PhotoMagic.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	rm *.o $(PROGRAM) $(TEST) PhotoMagic.a

lint:
	cpplint *.cpp *.hpp
