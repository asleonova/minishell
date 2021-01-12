/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:45:17 by monie             #+#    #+#             */
/*   Updated: 2021/01/12 13:53:32 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "headers/libft.h"
# include "headers/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

# define SUCCESS 0
# define FAIL 1

int	g_error;

typedef struct			s_env
{
	int					i;
	int					k;
	int					j;
	int					end;
	int					dollar;
	char				*env;
	char				*str;
}						t_env;

typedef struct			s_var
{
	int					j;
	int					k;
	int					i;
	int					q;
	char				oq;
	int					sq;
	int					dq;
	int					r;
	int					executor;
	int					shielding;
	int					np;
	char				*env;
	int					env_start;
	int					env_end;
	int					envf;
	char				*str;
	char				*arr;
	int					error;
	int					exception;
	t_list				*head;

	t_list				*list;
}						t_var;

typedef enum			e_command_names
{
	echo = 0,
	cd = 1,
	pwd = 2,
	export = 3,
	unset = 4,
	env = 5,
	our_exit = 6,
	bash = 7
}						t_command_names;

typedef struct			s_commands
{
	int					fd_0;
	int					fd_1;
	int					end;
	char				*cmd;
	int					invalid;
	t_command_names		command;
	int					count_args;
	int					save_1;
	int					save_0;
	int					fd_error;
	struct s_list		*arg_lst;
	struct s_commands	*next;
	struct s_commands	*prev;
}						t_commands;

typedef struct			s_data
{

	char				**envp;
	char				*path;
	char				*home;
	char				*status;
}						t_data;

int						ft_exit(t_commands *command);
int						ft_echo(t_commands *command);
int						ft_cd(t_commands *command, t_data *data);
void					free_tab(char **tab);
int						tab_len(char **tab);
int						ft_env(t_commands *command, t_data *data);
void					ft_export_update(t_data *data, char *str);
int						ft_export(t_data *data, t_commands *command);
int						ft_unset(t_data *data, t_commands *command);
int						ft_pwd();
void					ft_print_export(t_data *data);
int						path_exist(t_commands *command, t_data *data);
void					check_redirect(t_commands *command);
void					parse_func(t_commands *command, t_data *data);
void					change_env_values(char *var, t_data *data);
char					**ft_list_to_array(t_commands *command);
int						sysfunc_manager(t_commands *command, t_data *data);
void					executor(t_commands *command, t_data *data);
char					*get_env_values(t_data *data, char *key);
void					add_env_var(char *var, t_data *data);
void					delete_env_var(char *var, t_data *data);
void					ft_unset_env(char *str, t_data *data);
int						sysfunc_manager(t_commands *command, t_data *data);
void					command_for_exec(t_commands *command, t_data *data);
void					add_path_to_commands(t_commands *command, t_data *data);
void					handler(int signal);
int						exec_first_command(t_commands *command, \
						t_data *data, int pfd[2]);
void					execute(t_commands *command, t_data *data);
void					cmd_identifier(t_commands *command);
int						check_pipe(t_data *data, t_commands *command, \
						int pfd[2]);
int						count_list(t_commands *cmd);
void					execute_one_func(t_commands *command, t_data *data);
int						execute_execve(t_commands *command, t_data *data);
void					ft_swap(char **s1, char **s2);
void					ft_sort_list(t_data *data);
void					check_env_func(t_commands *cmd, t_data *data);
t_commands				*cmd_check(t_commands *cmd, t_data *data);
void					signals_default(void);
void					signals_ignore(void);
void					cd_zero_args(t_data *data);
int						error_path(t_commands *command);
int						error_identifier(t_commands *command);
int						error_no_file_or_dir(t_commands *command);
int						command_not_found(char *command);
void					permission_denied(t_commands *command);
int						path_no_file_or_dir(t_commands *command);
void					path_does_not_exist(t_commands *command, t_data *data);
int						syntax_error(void);
void					pid_error(void);
void					parser_str(t_var *var);
void					var_initialization(t_var *var);
void					cmd_initialization(t_commands *cmd);
void					create_lexer(t_var *var, int i);
void					clear_input_list(t_var *var);
void					analysis_lists(t_var *var, t_commands *cmd,\
						t_data *data, char ***env);
void					clear_struct(t_commands *cmd);
void					next_and_clear_args(t_commands *cmd);
int						distribution(char *str, t_var *var, \
						t_commands *cmd, int i);
void					processing_fd(t_var *var, t_commands *cmd);
void					parsing_env(t_var *var, char **env, char **str);
void					parsing_env_quote(t_var *var, char **env, char **str);
void					parsing_env_quote(t_var *var, char **env, char **str);
void					env_initialization(t_env *tmp);
void					env_initialization_step(t_env *tmp);
void					shielding(t_var *var, char **str, int i);
void					intro(void);
void					ft_free(char **str);
void					quote_cut(t_var *var, char **str, int i);
void					write_argv(t_var *var, t_commands *cmd);
void					write_cmd(char *str, t_commands *cmd, int i);

#endif
