CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

BUILD_DIR = build

DEPS = Universe.hpp CelestialBody.hpp
OBJECTS = $(BUILD_DIR)/Universe.o $(BUILD_DIR)/CelestialBody.o
PROGRAM = NBODY
TEST = test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all: $(PROGRAM) $(TEST) ./NBody.a

$(BUILD_DIR)/%.o: %.cpp $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/test.o: test.cpp $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c test.cpp -o $(BUILD_DIR)/test.o

$(PROGRAM): $(BUILD_DIR)/main.o $(OBJECTS) ./NBody.a
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

$(TEST): $(BUILD_DIR)/test.o $(OBJECTS) ./NBody.a
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

NBODY.a: $(OBJECTS)
	ar rcs ./NBody.a $(OBJECTS)

clean:
	rm -f $(BUILD_DIR)/*.o $(PROGRAM) $(TEST) ./NBody.a

# Linting
lint:
	cpplint *.cpp *.hpp
