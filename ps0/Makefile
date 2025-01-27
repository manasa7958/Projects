CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/Cellar/boost/1.85.0/include/ -I/opt/homebrew/Cellar/sfml/2.6.1/include/
LIBDIR = -L/opt/homebrew/Cellar/boost/1.85.0/lib/ -L/opt/homebrew/Cellar/sfml/2.6.1/lib/

# Your .hpp files
DEPS = 
# Your compiled .o files 
OBJECTS = 
# The name of your program
PROGRAM = sfml-app

.PHONY: all clean lint

all: $(PROGRAM)

# Wildcard recipe to make .o files from corresponding .cpp files 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

# Clean up build files
clean:
	rm -f *.o $(PROGRAM)

# Run linter on all source and header files
lint:
	cpplint *.cpp *.hpp
