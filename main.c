/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:55:41 by monie             #+#    #+#             */
/*   Updated: 2020/12/20 17:48:09 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void intro(void)
{
	write(1, "minishell: ", 11);
}

// int done(t_var *var)
// {
// 	if(!(ft_strncmp(var->str, "exit", 4)))
// 		return (0);
//  	return (1);
// }


// void clear_list(t_var *var)
// {
// 	t_list *tmp;
// 	while (var->list->prev)
// 	{
// 		free(var->list->content);
// 		tmp = var->list;
// 		var->list = var->list->prev;
// 		free(tmp);
// 	}
// 	free(var->list->content);
// 	free(var->list);
// 	var->list = NULL;
// }

// void clear_struct(t_commands *cmd)
// {
// 	t_list *tmp = NULL;
// 	while(cmd->arg_lst->prev)
// 	{
// 		free(cmd->arg_lst->content);
// 		tmp = cmd->arg_lst;
// 		cmd->arg_lst = cmd->arg_lst->prev;
// 		free(cmd->arg_lst->content);
// 		free(cmd->arg_lst);
// 		cmd->arg_lst = NULL;
// 	}
// }

void		copy_env(char **envp, t_data *data)
{
	int		len;
	int		i;

	i = 0;
	len = tab_len(envp);
	data->envp = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp[i] = 0;
}

int main(int argc, char **argv, char **envp) // мб потом выделить память на cmd и var;
{
	t_var	*var;
	t_commands *cmd;
	t_data	data;
	int 	i;
	
	i = 1;
	argc = 0;
	argv = NULL;
	copy_env(envp, &data);
	while(i)
	{
		signal(SIGINT, handler);
        signal(SIGQUIT, handler);
		var = malloc(sizeof(t_var));
		cmd = malloc(sizeof(t_commands));
		var_initialization(var);
		intro();
		get_next_line(0, &var->str);
		parser_str(var, envp);
		/* здесь буддет готовые листы полученные из строки */
		analysis_list(var, cmd);
		// clear_list(var);
		/* Анены функции */
		// printf("CMD1: %s\n", cmd->cmd);
		// printf("CMD2: %s\n", cmd->next->cmd);
		executor(cmd, &data);
		// clear_struct(&cmd);
		//i = done(&var);
		var_clear(var);
		var = NULL;
		// free(cmd);
		// cmd = NULL;
	}
	if(!i)
		write(1, "Error program", 14);
	return(0);
}