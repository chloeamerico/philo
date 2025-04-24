NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I.

# dossiers
SRCS_DIR	=	srcs/
OBJ_DIR		=	obj/

SRCS =  main.c \
	check_arg.c \
	free_and_destroy.c \
	routine.c \
	utils.c \

HEADER = philo.h

SRCS_PHILO 	=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS_PHILO 	= 	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# compilation
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS_PHILO)
	$(CC) $(CFLAGS) $(OBJS_PHILO) -o $(NAME) -lpthread

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re