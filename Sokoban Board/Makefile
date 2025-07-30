CC = g++
CFLAGS = -std=c++17 -Wall -Werror -pedantic -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

BUILD_DIR = build
DEPS = Sokoban.hpp
OBJECTS = $(BUILD_DIR)/Sokoban.o $(BUILD_DIR)/main.o
PROGRAM = Sokoban
STATIC_LIB = Sokoban.a

.PHONY: all clean lint

all: $(PROGRAM) $(STATIC_LIB)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIBS)

$(STATIC_LIB): $(BUILD_DIR)/Sokoban.o
	ar rcs $@ $^

clean:
	rm -rf $(BUILD_DIR) $(PROGRAM) $(STATIC_LIB)

lint:
	cpplint *.cpp *.hpp
