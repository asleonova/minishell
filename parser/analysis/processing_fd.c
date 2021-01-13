/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:21:30 by monie             #+#    #+#             */
/*   Updated: 2021/01/13 18:29:04 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		close_fd(int fd)
{
	close(fd);
	fd = -1;
	return (fd);
}

void	processing_fd(t_var *var, t_commands *cmd)
{
	if (var->list->next != NULL)
	{
		var->list = var->list->next;
		if (cmd->fd_1 != -1 && (var->r == 1 || var->r == 2))
			cmd->fd_1 = close_fd(cmd->fd_1);
		else if (cmd->fd_0 != -1 && var->r == 3)
			cmd->fd_1 = close_fd(cmd->fd_1);
		if (var->r == 1)
			cmd->fd_1 = open(var->list->content, O_RDWR | O_CREAT | \
			O_TRUNC, S_IWRITE | S_IREAD);
		else if (var->r == 2)
			cmd->fd_1 = open(var->list->content, O_RDWR | O_CREAT | \
			O_APPEND, S_IWRITE | S_IREAD);
		else if (var->r == 3)
			cmd->fd_0 = open(var->list->content, O_RDONLY);
		var->exception = 1;
		permission_denied(cmd);
	}
}
