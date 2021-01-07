/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:23:58 by monie             #+#    #+#             */
/*   Updated: 2021/01/07 14:22:58 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_arg_list(t_commands *cmd)
{
	t_list *tmp;

	free(cmd->cmd);
	cmd->cmd = NULL;
	while (cmd->arg_lst)
	{
		tmp = cmd->arg_lst->next;
		free(cmd->arg_lst->content);
		free(cmd->arg_lst);
		cmd->arg_lst = tmp;
	}
}

void	clear_struct(t_commands *cmd)
{
	t_commands *tmp;

	while (cmd)
	{
		clear_arg_list(cmd);
		tmp = cmd->next;
		free(cmd);
		cmd = NULL;
		cmd = tmp;
	}
}
