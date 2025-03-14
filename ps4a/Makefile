CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
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
	$(CXX) $(CXXFLAGS) $(INCLUDEDIR) -c $< -o $@

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBDIR) -o $@ $^ $(LIBS)

$(BUILD_DIR)/Sokoban.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	rm -rf $(BUILD_DIR) $(PROGRAM) $(BUILD_DIR)/Sokoban.a

lint:
	cpplint *.cpp *.hpp
