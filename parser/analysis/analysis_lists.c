/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:10:50 by monie             #+#    #+#             */
/*   Updated: 2021/01/11 15:55:48 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	write_argv(t_var *var, t_commands *cmd)
{
	ft_lstadd_back(&(cmd->arg_lst), ft_lstnew(ft_strdup(var->list->content)));
}

void	write_cmd(char *str, t_commands *cmd, int i)
{
	i = ft_strlen(str);
	cmd->cmd = malloc(i + 1);
	i = 0;
	while (str[i])
	{
		cmd->cmd[i] = str[i];
		i++;
	}
	cmd->cmd[i] = '\0';
}

void	analysis_lists(t_var *var, t_commands *cmd, t_data *data, char ***env)
{
	t_commands *tmp;
	int flag;

	tmp = NULL;
	flag = 0;
	cmd_initialization(cmd);
	while (var->list)
	{
		if (distribution(var->list->content, var, cmd, 0))
		{
			if (var->r && cmd->fd_error != 1)
				processing_fd(var, cmd);
			if (var->q == 2)
				parsing_env_quote(var, *env, &var->list->content);
			if (cmd->end)
			{
				if (var->list->next)
				{
					cmd_initialization(tmp = malloc(sizeof(t_commands)));
					tmp->prev = cmd;
					cmd->next = tmp;
					cmd = tmp;
				}
				else
					break ;
			}
		}
		if (var->q)
			quote_cut(var, &var->list->content, 0);
		if (var->list->content[0] == '$')
			parsing_env(var, *env, &var->list->content);
		if (!cmd->cmd && !var->exception)
			write_cmd(var->list->content, cmd, 0);
		else if (cmd->cmd && !var->exception)
			write_argv(var, cmd);
		if (!ft_strcmp(cmd->cmd, "export") && var->list->next == NULL)
		{
			cmd->count_args = ft_lstsize(cmd->arg_lst);
			if (cmd->count_args == 0)
			{	
				ft_print_export(data);	
				flag = 1;
			}

		}
		if (!ft_strcmp(cmd->cmd, "export") && flag == 0)
		{
			// cmd->count_args = ft_lstsize(cmd->arg_lst);
			// printf("COUNT_ARGS: %d\n", cmd->count_args);
			// if (cmd->count_args == 0 && cmd->arg_lst == NULL) 
			// 	ft_print_export(data);
			while (cmd->arg_lst)
				ft_export(data, cmd);
		}
		if (var->list->next != NULL)
			var->list = var->list->next;
		else
			break ;
	}
}
