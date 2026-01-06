MAKEFLAGS += -s

NAME = Skyscraper

INCLUDE = includes
SRC_DIR = src
OBJ_DIR = objs

CC = cc
FLAGS = -Wall -Wextra -Werror -g

FILES = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(FILES))

CYAN = "\033[36m"
RED    = "\033[31m"
GREEN = "\033[32m"
RESET = "\033[0m"

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(CYAN)"Compiling $(NAME)..."$(RESET)
	@$(CC) $(FLAGS) $(OBJS) -I $(INCLUDE) -o $(NAME)
	@echo $(GREEN)"$(NAME) executable created !"$(RESET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	@echo $(GREEN)"Objets files cleared !"$(RESET)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo $(GREEN)"$(NAME) cleared !"$(RESET)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re