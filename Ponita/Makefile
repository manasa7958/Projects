CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework

DEPS = CelestialBody.hpp Universe.hpp
OBJECTS = CelestialBody.o Universe.o
PROGRAM = NBody
TEST = test

.PHONY: all clean lint

all: $(PROGRAM) $(TEST) NBody.a

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): $(OBJECTS) main.o
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) main.o $(LIB)

$(TEST): $(OBJECTS) test.o
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) test.o $(LIB)

NBody.a: $(OBJECTS)
	ar rcs $@ $^

clean:
	rm -f *.o $(PROGRAM) $(TEST) NBody.a

lint:
	cpplint *.cpp *.hpp
