/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:55:41 by monie             #+#    #+#             */
/*   Updated: 2021/01/07 17:56:29 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void intro(void)
{
	write(1, "minishell: ", 11);
}

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

void	see_input_lists(t_var *var)
{
	if (var->list)
	{
		while (var->list->prev)
			var->list = var->list->prev;
		while (var->list->next)
		{
			printf("var->list\t%s\n", var->list->content);
			var->list = var->list->next;
		}
		printf("var->list\t%s\n", var->list->content);
	}
}

void	see_analysis_lists(t_commands *cmd)
{
	printf("cmd->cmd\t%s\n", cmd->cmd);
	printf("cmd->fd_1\t%d\ncmd->fd_0\t%d\n", cmd->fd_1, cmd->fd_0);
	if (cmd->arg_lst)
	{
		while (cmd->arg_lst->next)
		{
			printf("cmd->arg_list\t%s\n", cmd->arg_lst->content);
			cmd->arg_lst = cmd->arg_lst->next;
		}
		printf("cmd->arg_list\t%s\n", cmd->arg_lst->content);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_var	*var;
	t_commands *cmd;
	t_data	data;
	int 	i;
	int		ret;
	
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
		cmd_initialization(cmd);
		intro();
		ret = get_next_line(0, &var->str);
		if (ret == 666)
		{
			ft_putstr_fd("exit\n", 1);
			exit(g_error);
		}
		parser_str(var);
		/* здесь буддет готовые листы полученные из строки */
		analysis_lists(var, cmd, &data, &data.envp);
		executor(cmd, &data);
		//see_input_lists(var);
		// while (cmd)
		// {
		// 	see_analysis_lists(cmd);
		// 	if (cmd->next)
		// 		cmd = cmd->next;
		// 	else
		// 		break ;
		// }
		clear_input_list(var);
		clear_struct(cmd);
	}
	return(0);
}