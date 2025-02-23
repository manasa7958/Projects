# Compiler and Flags
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

# Directories
BUILD_DIR = build

# Source files and dependencies
DEPS = Universe.hpp CelestialBody.hpp
OBJECTS = $(BUILD_DIR)/Universe.o $(BUILD_DIR)/CelestialBody.o
PROGRAM = NBODY
TEST = test

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Default target: Compile everything
all: $(PROGRAM) $(TEST) NBODY.a

# Compile .cpp files into .o files inside build/
$(BUILD_DIR)/%.o: %.cpp $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

# Compile the main program
$(PROGRAM): $(BUILD_DIR)/main.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

# Compile the test program separately
$(TEST): $(BUILD_DIR)/test.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIB)

# Create a static library
NBODY.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

# Clean up compiled files
clean:
	rm -rf $(BUILD_DIR) $(PROGRAM) $(TEST) NBODY.a

# Run cpplint for linting
lint:
	cpplint *.cpp *.hpp
