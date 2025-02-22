CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

# Source files
DEPS = Universe.hpp CelestialBody.hpp
OBJECTS = build/Universe.o build/CelestialBody.o
PROGRAM = NBODY
TEST = test

.PHONY: all clean lint

all: $(PROGRAM) $(TEST) NBODY.a

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

$(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

NBODY.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	rm *.o $(PROGRAM) $(TEST)

lint:
	cpplint *.cpp *.hpp
