NAME = minishell
LIBFT = libft.a

HEADER = ./minishell.h

DBLISS = ./executor/cmd.c \
		./executor/cd.c \
		./executor/echo.c \
		./executor/env_vars.c \
		./executor/env.c \
		./executor/errors.c \
		./executor/executor.c \
		./executor/utils.c \
		./executor/export.c \
		./executor/our_exit.c \
		./executor/pipes.c \
		./executor/pwd.c \
		./executor/unset.c \
		./executor/paths.c \
		./executor/count_lists.c \
		./executor/cmd_check.c \
		./signals/signals.c

MONIE = ./initialization/var_initialization_clear.c  \
		./initialization/cmd_initialization.c \
		./initialization/env_initialization.c \
		./parser/input_lists/create_lexer.c \
		./parser/input_lists/parser_str.c \
		./parser/input_lists/clear_input_list.c \
		./parser/analysis/analysis_lists.c \
		./parser/analysis/clear_struct.c \
		./parser/analysis/distribution.c \
		./parser/analysis/processing_fd.c \
		./parser/analysis/parsing_env.c \
		./parser/analysis/parsing_env_quote.c \
		./parser/analysis/shielding.c \
		./parser/analysis/quote_cut.c \
		./parser/analysis/parsing_errors.c \
		./parser/analysis/write_argv.c \
		./parser/analysis/write_cmd.c
		
SRCS = ./main.c \
	$(MONIE) \
	$(DBLISS)

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
debug: 
	clang -Iheaders libft/*.c $(SRCS) -o $(NAME) -g
.PHONY: all clean flean re