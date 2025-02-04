# Compiler and flags
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

DEPS = FibLFSR.hpp
OBJECTS = FibLFSR.o
LIBRARY = PhotoMagic.a
PROGRAM = test

.PHONY: all clean lint

all: $(LIBRARY) $(PROGRAM) PhotoMagic

PhotoMagic: FibLFSR.o
    $(CC) $(CFLAGS) -o PhotoMagic FibLFSR.o $(LIBDIR) $(LIB)

%.o: %.cpp $(DEPS)
    $(CC) $(CFLAGS) -c $< -o $@ $(INCLUDEDIR)

$(LIBRARY): $(OBJECTS)
    ar rcs $(LIBRARY) $(OBJECTS)

$(PROGRAM): test.o $(LIBRARY)
    $(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

clean:
    rm -f *.o $(PROGRAM) $(LIBRARY) PhotoMagic

lint:
    cpplint *.cpp *.hpp

