NAME = minishell
LIBFT = libft.a

HEADER = ./minishell.h

SRCS = ./main.c \
	./parser/parser_str.c \
	./initialization/var_initialization_clear.c  \
	./parser/create_lexer.c \
	./parser/analysis_list.c \
	./initialization/cmd_initialization.c \
	./parser/print_list.c \
	./signals/signals.c \
	./executor/cmd.c \
	./executor/cd.c \
	./executor/echo.c \
	./executor/env_vars.c \
	./executor/env.c \
	./executor/errors.c \
	./executor/executor.c \
	./executor/export.c \
	./executor/our_exit.c \
	./executor/pipes.c \
	./executor/pwd.c \
	./executor/unset.c \
	./executor/sysfuncs.c


OBJ = $(SRCS:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

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
debug: 
	clang -Iheaders libft/*.c $(SRCS) -o $(NAME) -g
.PHONY: all clean flean re