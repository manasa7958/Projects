CC = g++
CFLAGS = -std=c++17 -Wall -Werror -pedantic -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
BOOST_LIB = -lboost_unit_test_framework

INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

BUILD_DIR = build
DEPS = RandWriter.hpp
OBJECTS = $(BUILD_DIR)/RandWriter.o $(BUILD_DIR)/TextWriter.o
TEST_OBJECTS = $(BUILD_DIR)/RandWriter.o $(BUILD_DIR)/test.o
PROGRAM = TextWriter
STATIC_LIB = TextWriter.a
TEST = test

.PHONY: all clean lint test

all: $(PROGRAM) $(STATIC_LIB) $(TEST)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^

$(STATIC_LIB): $(BUILD_DIR)/RandWriter.o
	ar rcs $@ $^

$(TEST): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(BOOST_LIB)

clean:
	rm -rf $(BUILD_DIR) $(PROGRAM) $(STATIC_LIB) $(TEST)

lint:
	cpplint *.cpp *.hpp
