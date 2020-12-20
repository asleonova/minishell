#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>  //------------DELETE------------//

#define SUCCESS 0
#define FAIL 1

int g_error;
char **envp;

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

typedef enum    e_command_names
{
    echo = 0,
    cd = 1,
    pwd = 2,
    export = 3,
    unset = 4,
    env = 5,
    our_exit = 6,
    bash = 7
}               t_command_names;

typedef struct          s_commands
{
    int                 fd_0;
    int                 fd_1;
	int					end; /* ;=1 or | = 2 if 0 = '\0' */
    char				*cmd; /* command */
    int                 invalid; // флаг - команда невалидна, 1
    t_command_names     command;
    int                 count_args;
    struct s_list       *arg_lst; // лист с аргументами команды, то есть echo hello world, hello - лсит№1, world лист #2
	struct s_commands	*next;
	struct s_commands	*prev;
}                       t_commands;

typedef struct          s_data
{

    char                **envp; // переменные окружения (длинный список) - type in termibal env to see how it looks like
    char                *path; // PATH= 
    char                *home;
}                       t_data;

void ft_exit(t_commands *command);
int ft_cd(t_commands *command, t_data *data);
int ft_echo(t_commands *command);
void		free_tab(char **tab);
int		tab_len(char **tab);
int ft_env(t_data *data, t_commands *command);
void ft_export_update(t_data *data, char *str);
int			ft_export(t_data *data, t_commands *command);
void ft_unset(t_data *data, t_commands *command);
int ft_pwd();

// executor: maybe delete some static 
void    check_redirect(t_commands *command);
int parse_func(t_commands *command, t_data *data);
void	change_env_value(char *var, t_data *data);
char **ft_list_to_array(t_commands *command);
int sysfunc_manager(t_commands *command, t_data *data);
void executor(t_commands *command, t_data *data);
void pipe_manager(t_commands *command, t_data *data);
char *get_env_values(t_data *data, char *key);
void		add_env_var(char *var, t_data *data);
void	delete_env_var(char *var, t_data *data);
void		ft_unset_env(char *str, t_data *data);


void handler(int signal);

// custom errors:
int error_path(t_commands *command);
int error_identifier(t_commands *command);
int error_no_file_or_dir(t_commands *command);
int command_not_found(t_commands *command);

// Den: 
void	parser_str(t_var *var);
void	var_initialization(t_var *var);
void	var_clear(t_var *var);
void	create_lexer(t_var *var, int i);
void	analysis_list(t_var *var, t_commands *cmd);
void	cmd_initialization(t_commands *cmd);
int     print_list(t_commands *cmd);
void intro(void);
#endif