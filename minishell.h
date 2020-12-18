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

extern int g_error;

typedef struct  s_syntax
{
	int		i;
	int		y; 
	int		f;	/* >  >> <*/
	int		mf;	/* > */
	int		lf;	/* < */
	int		ff; /* >> */
	int		pf; /* \ */
	int		ef; /* error */
	int		cf; /* cmd flag */
	int		envf; /* env flag */
	int		fd_input;
	int		fd_output;
	int		cmdf;
}               t_syntax;

typedef struct  s_var
{
	int		i; // конец строки или конец команды
	int		j; // позиция конца слова
	int		k; // позиция в токене
	int		cf; //special character >> > <
	int		ef; // end of command
	int		sf; // single quotes
	int		df; // double quotes
	int		quote; // write single 1 or double 2
	int		pip; /* | */
	int		semicolon; /* ; */
	char	*str; // array in
	char	*arr; // recording array
	char	**arg; // my array
	int		error; //
	char	**env; /* recording env */
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

typedef enum    e_redirect // установить сначала -1!!!!
{
    redir = 1, // >
    double_redir = 2, // >>
    back_redir = 3 // <
}               t_redirect;

typedef struct          s_commands
{
    int                 fd_0;
    int                 fd_1;
    char                *cmd; // команда (например echo)
    int                 count_args; // кол-во аргументов для команды (например echo hello world будет 2, так как hello - 1, world - 2 отдельно)
    int                 invalid; // флаг - команда невалидна, 1
    int                 status;
    t_command_names     cmd_list;
    t_redirect          type_redir;
    struct s_list       *lst; // лист с аргументами команды, то есть echo hello world, hello - лсит№1, world лист #2
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

// executor: maybe delete some static 
int		check_redirect(t_commands *command);
int parse_func(t_commands *command, t_data *data);
char **ft_list_to_array(t_commands *command);
int sysfunc_manager(t_commands *command, t_data *data);
void executor(t_commands *command, t_list *lst, t_data *data);
int pipe_manager(t_commands *command, t_data *data);

void handler(int signal);

// custom errors:
int error_path(t_commands *command);
int error_identifier(t_commands *command);
int error_no_file_or_dir(t_commands *command);
int command_not_found(t_commands *command);

// Den: 
int parser(t_var *var);
int parser_cmd(t_var *var);
int parser_on_lexer(t_var *var);
int analysis(t_var *var);
int create_lexer(t_var *var, int i);
int create_argument(t_var *var);
int		analysis_list(t_var *var, char ***env);
void processing_fd(char *str, t_syntax *syntax);
void parsing_env(char ***env, char **str);
int	distribution(char *str, t_syntax *syntax, int i);
void intro(void);

#endif