CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

# Your .hpp files
DEPS = triangle.hpp
# Your compiled .o files
OBJECTS = triangle.o
# The name of your program
PROGRAM = Triangle

.PHONY: all clean lint

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

clean:
	rm -f *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp
