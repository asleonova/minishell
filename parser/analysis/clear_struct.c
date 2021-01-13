/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:23:58 by monie             #+#    #+#             */
/*   Updated: 2021/01/13 18:40:41 by monie            ###   ########.fr       */
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
		printf("cmd->arg_lst\t%s\n", cmd->arg_lst->content);
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
		printf("cmd->cmd\t%s\n", cmd->cmd);
		clear_arg_list(cmd);
		tmp = cmd->next;
		free(cmd);
		cmd = NULL;
		cmd = tmp;
	}
}

void	next_and_clear_args(t_commands *cmd)
{
	t_list *tmp;

	tmp = cmd->arg_lst->next;
	free(cmd->arg_lst->content);
	free(cmd->arg_lst);
	cmd->arg_lst = tmp;
}
