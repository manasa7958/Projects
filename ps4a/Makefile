CC = g++
CFLAGS = -std=c++17 -Wall -Werror -pedantic -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/ -I/opt/homebrew/opt/sfml@2/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/ -L/opt/homebrew/opt/sfml@2/lib/

BUILD_DIR = build
DEPS = Sokoban.hpp
OBJECTS = $(BUILD_DIR)/Sokoban.o $(BUILD_DIR)/main.o
PROGRAM = Sokoban

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all: $(PROGRAM) $(BUILD_DIR)/Sokoban.a

$(BUILD_DIR)/%.o: %.cpp $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(LIBS)

$(BUILD_DIR)/Sokoban.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	rm -rf $(BUILD_DIR) $(PROGRAM) $(BUILD_DIR)/Sokoban.a

lint:
	cpplint *.cpp *.hpp
