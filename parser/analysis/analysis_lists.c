/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:10:50 by monie             #+#    #+#             */
/*   Updated: 2021/01/11 19:05:22 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		analysis_zero(t_var *var, t_commands *cmd)
{
	t_commands *tmp;

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
			return (1);
	}
	return (0);
}

int		analysis_one(t_var *var, t_commands *cmd, char ***env)
{
	if (distribution(var->list->content, var, cmd, 0))
	{
		if (var->list->content[0] == '>' || var->list->content[0] == '<')
		{
			syntax_error();
			return (1);
		}
		if (var->r && cmd->fd_error != 1)
			processing_fd(var, cmd);
		if (var->q == 2)
			parsing_env_quote(var, *env, &var->list->content);
		if (analysis_zero(var, cmd))
			return (1);
	}
	return (0);
}

void	analysis_tho(t_var *var, t_commands *cmd, char ***env)
{
	if (var->q)
		quote_cut(var, &var->list->content, 0);
	if (var->list->content[0] == '$')
		parsing_env(var, *env, &var->list->content);
	if (!cmd->cmd && !var->exception)
		write_cmd(var->list->content, cmd, 0);
	else if (cmd->cmd && !var->exception)
		write_argv(var, cmd);
}

int		analysis_three(t_var *var, t_commands *cmd, t_data *data, int flag)
{
	if (!ft_strcmp(cmd->cmd, "export") && flag == 0)
	{
		while (cmd->arg_lst)
			ft_export(data, cmd);
	}
	if (var->list->next != NULL)
		var->list = var->list->next;
	else
		return (1);
	return (0);
}

void	analysis_lists(t_var *var, t_commands *cmd, t_data *data, char ***env)
{
	int flag;

	flag = 0;
	cmd_initialization(cmd);
	while (var->list)
	{
		if (analysis_one(var, cmd, env))
			break ;
		analysis_tho(var, cmd, env);
		if (!ft_strcmp(cmd->cmd, "export") && var->list->next == NULL)
		{
			cmd->count_args = ft_lstsize(cmd->arg_lst);
			if (cmd->count_args == 0)
			{
				ft_print_export(data);
				flag = 1;
			}
		}
		if (analysis_three(var, cmd, data, flag))
			break ;
	}
}
