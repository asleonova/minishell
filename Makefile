NAME = minishell
LIBFT = libft.a

HEADER = ./minishell.h

#SRCS = ./executor/custom_commands.c
SRCS = main_old.c

OBJ = $(SRCS:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ) $(HEADER) 
	$(MAKE) -C ./libft all
	$(CC) $(CFLAGS) ./libft/$(LIBFT) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER) 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ./libft fclean
	rm -f $(OBJ)
fclean: clean
	$(MAKE) -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean flean re