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

all: $(PROGRAM) $(TEST) NBODY.a

.PHONY: all clean lint

build:
	mkdir -p build

# Compile all .cpp files to .o
build/%.o: %.cpp $(DEPS) | build
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

$(PROGRAM): build/main.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

$(TEST): build/test.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

clean:
	rm -rf build $(PROGRAM) $(TEST)

lint:
	cpplint *.cpp *.hpp

