CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

BUILD_DIR = build

DEPS = Universe.hpp CelestialBody.hpp
OBJECTS = $(BUILD_DIR)/Universe.o $(BUILD_DIR)/CelestialBody.o
PROGRAM = NBody
TEST = test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all: $(PROGRAM) $(TEST) NBody.a

$(BUILD_DIR)/%.o: %.cpp $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

$(PROGRAM): $(BUILD_DIR)/main.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

$(TEST): $(BUILD_DIR)/test.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

NBody.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	rm -rf $(BUILD_DIR) $(PROGRAM) $(TEST) NBody.a

lint:
	cpplint *.cpp *.hpp
