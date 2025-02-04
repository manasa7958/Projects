# Compiler and flags
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

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
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

PhotoMagic.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp

