# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g

# Dossiers
SRC_DIR = srcs
OBJ_DIR = obj
BIN_DIR = bin

# Fichiers sources
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/assembler_interpreter.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/movements.c \
       $(SRC_DIR)/comparisons.c \
       $(SRC_DIR)/labels.c \
       $(SRC_DIR)/globals.c \
       $(SRC_DIR)/message.c

# Génération des objets
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Nom du binaire
TARGET = $(BIN_DIR)/asm_interpreter

# Règles
all: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re
