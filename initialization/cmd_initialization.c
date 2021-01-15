/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:47:55 by monie             #+#    #+#             */
/*   Updated: 2021/01/12 20:06:44 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_initialization(t_commands *cmd)
{
	cmd->cmd = NULL;
	cmd->arg_lst = NULL;
	cmd->end = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fd_0 = -1;
	cmd->fd_1 = -1;
	cmd->fd_error = 0;
	cmd->cmd_error = NULL;
}
