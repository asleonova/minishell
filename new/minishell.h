#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <stdio.h> //---------------------DELETE
# include <fcntl.h>

extern int g_error;
extern char **envp;

typedef struct  s_var
{
	int		i; /* end string */
	int		j; /*  */  // позиция конца слова
	int		k; // позиция в токене
	char	*str; // array in
	char	*arr; /* array write list */
	int		error; /* errors */
	int		rf; /* > */
	int		df; /* >> */
	int		rif; /* < */
	t_list	*list;
}               t_var;

typedef enum	e_command_list
{
	echo = 0,
	cd = 1,
	pwd = 2,
	export = 3,
	unset = 4,
	env = 5,
	our_exit = 6,
	bash = 7
}               t_command_list;

typedef struct			s_commands
{
	char				*cmd; /* command */
	int					end; /* ;=1 or | = 2 if 0 = '\0' */
	int					fd_0; 
	int					fd_1;
	t_command_list		command;
	struct s_list		*arg_list; // лист с аргументами команды, то есть echo hello world, hello - лсит№1, world лист #2
	struct s_commands	*next;
	struct s_commands	*prev;
}						t_commands;
	 
typedef struct          s_data
{
	int                 fd_0;
	int                 fd_1;
	char                **envp; // переменные окружения (длинный список) - type in termibal env to see how it looks like
	int                 home_dir; // порядковый номер переменной окружения в домашней директории HOME
	int                 current_pwd; // текущиий pwd PWD=
	int                 old_pwd; // OLDPWD=
	int                 env_var; // мб вновь созданные переменные окружения
	int                 path; // PATH= 
	int                 count_str; // кол-во строк
	char                *error_string; // текст ошибки
}                       t_data;

void	parser_str(t_var *var);
void	var_initialization(t_var *var);
void	var_clear(t_var *var);
void	create_lexer(t_var *var, int i);
void	analysis_list(t_var *var, t_commands *cmd);
void	cmd_initialization(t_commands *cmd);
void	print_list(t_commands *cmd);
#endif