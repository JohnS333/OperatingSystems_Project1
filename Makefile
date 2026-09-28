# Compiler and flags
CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -std=c99 -pedantic -D_POSIX_C_SOURCE=200809L -Iinclude -g

# Directories
SRC_DIR  := src
INC_DIR  := include
BIN_DIR  := bin
OBJ_DIR  := obj

# Target Executable
TARGET   := $(BIN_DIR)/shell

# Dynamically gather all .c files in src/
SRCS     := $(wildcard $(SRC_DIR)/*.c)
OBJS     := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Link all compiled object files into bin/shell
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compile each src/%.c into obj/%.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create required output directories if they don't exist
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean target to wipe generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean