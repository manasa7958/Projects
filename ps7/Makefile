CC = g++
CFLAGS = -std=c++17 -Wall -Werror -pedantic -g

BOOST_LIB = -lboost_date_time
INCLUDEDIR = -I. -I/opt/homebrew/opt/boost/include/
LIBDIR = -L/opt/homebrew/opt/boost/lib/
BUILD_DIR = build

SRCS = ps7.cpp
OBJS = $(BUILD_DIR)/ps7.o
EXEC = ps7

.PHONY: all clean lint ps7

all: $(EXEC)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $^ $(BOOST_LIB)

clean:
	rm -rf $(BUILD_DIR) $(EXEC) *.rpt

lint:
	cpplint *.cpp *.hpp
