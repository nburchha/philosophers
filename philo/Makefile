NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I includes
SRC_DIR = srcs
OBJ_DIR = .obj

SRC_FILES = main.c init.c util.c cleanup.c logging.c routine.c monitor.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

GREEN=\033[32m
RED=\033[31m
RESET=\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Removing objects$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)$(RESET)"
	@rm -f $(NAME)

re: fclean all

bonus:
	@make -C ../philo_bonus

.PHONY: clean fclean re all bonus
