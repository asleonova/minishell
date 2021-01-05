/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:23:58 by monie             #+#    #+#             */
/*   Updated: 2021/01/02 13:10:15 by monie            ###   ########.fr       */
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

void	clear_struct(t_commands *cmd)
{
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
