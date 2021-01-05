/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:10:50 by monie             #+#    #+#             */
/*   Updated: 2021/01/05 13:35:19 by monie            ###   ########.fr       */
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

int		analysis_lists_utils(t_var *var, t_commands *cmd, char **env, t_commands *tmp)
{
	if (distribution(var->list->content, var, cmd, 0))
	{
		if (var->r)
			processing_fd(var, cmd);
		if (var->q == 2)
			parsing_env_quote(var, env, &var->list->content);
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
	}
	return (0);
}
void	analysis_lists(t_var *var, t_commands *cmd, char **env)
{
	t_commands *tmp;

	tmp = NULL;
	cmd_initialization(cmd);
	while (var->list)
	{
		if(analysis_lists_utils(var, cmd, env, tmp))
			break ;
		if (var->list->content[0] == '$')
			parsing_env(var, env, &var->list->content);
		if (!cmd->cmd && !var->exception)
			write_cmd(var->list->content, cmd, 0);
		else if (cmd->cmd && !var->exception)
			write_argv(var, cmd);
		if (var->list->next != NULL)
			var->list = var->list->next;
		else
			break ;
	}
}
