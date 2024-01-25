# SETUP
NAME		=	philo_bonus

CFLAGS		=	-Wall -Wextra -Werror -g
CCHECK		=	-g -fsanitize=thread
RM			=	rm -rf
INCLUDE		=	-I./include

SRC_FILES	=	philo.c utils.c init.c thread.c
SRC_DIR		=	src/
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		=	obj/
OBJ			=	$(addprefix $(OBJ_DIR),$(SRC_FILES:%.c=%.o))


# RULES
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		@cc $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		@cc $(OBJ) -o $(NAME)
		@echo "\n$(YELLOW)Compiling...$(DEFAULT)\n"
		@echo "\n$(GREEN)philo created!$(DEFAULT)\n"

check: $(OBJ)
		@cc $(CCHECK) $(OBJ) -o $(NAME)

clean: 
		@$(RM) $(OBJ_DIR)
		@echo "\n$(RED)Objects cleaned!$(DEFAULT)\n"

fclean: clean
		@$(RM) $(NAME)
		@echo "\n$(RED)philo cleaned!$(DEFAULT)\n"

re: fclean all

.PHONY: all clean fclean re check

# COLORS
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
DEFAULT	=	\033[0m