# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g -I./src
LDFLAGS =

# Directories
SRC_DIR = src
BUILD_DIR = build

# find all .c files in SRC_DIR
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Convert every src/%.c into build/%.o
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Target executable
TARGET = stat

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $@

# Link: build/%.o -> calc
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile: src/%.c -> build/%.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
.PHONY: clean all

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
