NAME = minishell
LIBFT = libft.a

HEADER = ./minishell.h

SRCS = ./main.c \
		./lexer/parser/parser.c \
		./lexer/parser/analysis.c \
		./lexer/parser/create.c \
		./lexer/analysis/analysis_list.c
		./lexer/analysis/processing_fd.c \
		./lexer/env/env.c \
		./lexer/analysis/distribution.c \
		./executor/cd.c \
		./executor/echo.c \
		./executor/env_vars.c \
		./executor/env.c \
		./executor/errors.c \
		./executor/our_exit.c \
		./executor/pwd.c \
		./executor/unset.c \
		./signals/signals.c
		

OBJ = $(SRCS:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) -Iheaders libft/$(LIBFT) $(OBJ) -o $(NAME)

$(GNL):
	$(MAKE) -C ./libft all

$(LIBFT):
	$(MAKE) -C ./libft all

%.o: %.c $(HEADER) 
	$(CC) $(CFLAGS) -Iheaders -c $< -o $@

clean:
	$(MAKE) -C ./libft fclean
	rm -f $(OBJ)
fclean: clean
	$(MAKE) -C ./libft fclean
	rm -f $(NAME)

re: fclean all
debag: 
	clang -Iheaders libft/*.c $(SRCS) -o $(NAME) -g
.PHONY: all clean flean re