CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

BUILD_DIR = build

DEPS = Universe.hpp CelestialBody.hpp main.cpp
OBJECTS = $(BUILD_DIR)/Universe.o $(BUILD_DIR)/CelestialBody.o $(BUILD_DIR)/main.o
PROGRAM = NBody
TEST = test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all: $(PROGRAM) $(TEST)

$(BUILD_DIR)/%.o: %.cpp $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

$(TEST): $(BUILD_DIR)/test.o $(OBJECTS)
	$(CC) $(CFLAGS) -DBOOST_TEST_DYN_LINK $(LIBDIR) -o $@ $^ $(LIB)

clean:
	rm -rf $(BUILD_DIR) $(PROGRAM) $(TEST)

lint:
	cpplint *.cpp *.hpp
