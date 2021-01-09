/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:10:50 by monie             #+#    #+#             */
/*   Updated: 2021/01/09 19:04:11 by monie            ###   ########.fr       */
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

void	my_export(t_commands *cmd, t_data *data)
{
	while (cmd->arg_lst)
	{
		ft_export_update(data, cmd->arg_lst->content);
		cmd->arg_lst = cmd->arg_lst->next;
	}
}

void	quote_cut(t_var *var, char **str, int i, int k)
{
	char *new_str;

	i = ft_strlen(*str);
	new_str = malloc(i);
	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '\'' || str[0][i] == '"')
		{
			if (var->oq != '\'' && var->oq != '"')
				var->oq = (str[0][i] == '\'') ? '\'' : '"';
			if (var->oq == str[0][i])
				i++;
		}
		new_str[k++] = str[0][i++];
	}
	new_str[k] = '\0';
	free(*str);
	*str = NULL;
	*str = ft_strdup(new_str);
	free(new_str);
	new_str = NULL;
}

int		analysis_utils(t_var *var, t_commands *cmd, t_data *data, char ***env)
{
	t_commands *tmp;

	if (distribution(var->list->content, var, cmd, 0))
	{
		if (var->shielding)
			shielding(var, &var->list->content, 0, 0);
		if (var->r)
			processing_fd(var, cmd);
		if (var->q == 2)
			parsing_env_quote(var, *env, &var->list->content);
		if (cmd->end)
		{
			if (cmd->end == 2)
				executor(cmd, data);
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

void	analysis_lists(t_var *var, t_commands *cmd, t_data *data, char ***env)
{
	cmd_initialization(cmd);
	while (var->list)
	{
		if (analysis_utils(var, cmd, data, env))
			break ;
		if (var->q)
			quote_cut(var, &var->list->content, 0, 0);
		if (var->list->content[0] == '$' && !var->np)
			parsing_env(var, *env, &var->list->content);
		if (!cmd->cmd && !var->exception)
			write_cmd(var->list->content, cmd, 0);
		else if (cmd->cmd && !var->exception)
			write_argv(var, cmd);
		if (var->list->next != NULL)
			var->list = var->list->next;
		else
			break ;
	}
	if (!ft_strcmp(cmd->cmd, "export"))
		my_export(cmd, data);
	if (cmd->end != 2)
		executor(cmd, data);
}
