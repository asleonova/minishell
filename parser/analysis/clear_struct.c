/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:23:58 by monie             #+#    #+#             */
/*   Updated: 2021/01/06 14:24:43 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_arg_list(t_commands *cmd)
{
	t_list *tmp;

	tmp = NULL;
	free(cmd->cmd);
	cmd->cmd = NULL;
	if (cmd->arg_lst)
	{
		while (cmd->arg_lst->prev != NULL)
		{
			free(cmd->arg_lst->content);
			cmd->arg_lst->content = NULL;
			tmp = cmd->arg_lst;
			cmd->arg_lst = cmd->arg_lst->prev;
			free(tmp);
		}
		free(cmd->arg_lst->content);
		free(cmd->arg_lst);
		cmd->arg_lst = NULL;
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

void	struct_end(t_commands *cmd)
{
	while (cmd)
	{
		// see_analysis_lists(cmd);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
}

void	clear_struct(t_commands *cmd)
{
	struct_end(cmd);
	while (cmd)
	{
		clear_arg_list(cmd);
		free(cmd->cmd);
		cmd->cmd = NULL;
		if (cmd->prev)
		{
			cmd = cmd->prev;
			free(cmd->next);
			cmd->next = NULL;
		}
		else
			break ;
	}
	free(cmd);
	cmd = NULL;
}
