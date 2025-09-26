NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
SRC_FILES = main.c init.c util.c cleanup.c logging.c routine.c monitor.c
OBJS = $(addprefix .obj/, $(SRC_FILES:.c=.o))
GREEN=\033[32m
RED=\033[31m
RESET=\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

.obj/%.o: src/%.c
	@echo "$(GREEN)Compiling $<$(RESET)"
	@mkdir -p .obj
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	@echo "$(RED)Removing $(OBJS)$(RESET)"
	@rm -f $(OBJS)
fclean: clean
	@echo "$(RED)Removing $(NAME)$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME)
re: fclean $(NAME)

.PHONY: clean fclean re all bonus