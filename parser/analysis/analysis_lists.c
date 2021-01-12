/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:10:50 by monie             #+#    #+#             */
/*   Updated: 2021/01/12 20:21:46 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void			analysis_one(t_var *var, t_commands *cmd, char ***env)
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

void			analysis_export(t_var *var, t_commands *cmd, t_data *data,
		int flag)
{
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
		while (cmd->arg_lst)
			ft_export(data, cmd);
	}
}

void			analysis_two(t_var *var, t_commands *cmd, char ***env)
{
	if ((var->list->content[0] == '>' || var->list->content[0] == '<') && \
		(var->list->next->content[0] == '>' || \
		var->list->next->content[0] == '<'))
		syntax_error(var);
	if (var->r && cmd->fd_error != 1)
		processing_fd(var, cmd);
	if (var->q == 2)
		parsing_env_quote(var, *env, &var->list->content);
}

t_commands		*analysis_three(t_commands *cmd)
{
	t_commands *tmp;

	cmd_initialization(tmp = malloc(sizeof(t_commands)));
	tmp->prev = cmd;
	cmd->next = tmp;
	cmd = tmp;
	return (cmd);
}

void			analysis_lists(t_var *var, t_commands *cmd, t_data *data,
		char ***env)
{
	int flag;

	flag = 0;
	cmd_initialization(cmd);
	while (var->list)
	{
		if (distribution(var->list->content, var, cmd, 0))
		{
			analysis_two(var, cmd, env);
			if (cmd->end)
			{
				if (var->list->next)
					cmd = analysis_three(cmd);
			}
		}
		analysis_one(var, cmd, env);
		analysis_export(var, cmd, data, flag);
		if (var->list->next != NULL)
			var->list = var->list->next;
		else
			break ;
	}
}
