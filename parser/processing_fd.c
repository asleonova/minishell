/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:53:44 by monie             #+#    #+#             */
/*   Updated: 2020/12/21 17:24:48 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int close_fd(int fd)
{
	close(fd);
	fd = -1;
	return(fd);
}

void processing_fd(t_var *var, t_commands *cmd)
{
	if(var->list->next != NULL)
	{
		var->list = var->list->next;
		if(cmd->fd_1 != -1)
			cmd->fd_1 = close_fd(cmd->fd_1);
		else if(cmd->fd_0 != -1)
			cmd->fd_1 = close_fd(cmd->fd_1);
		if(var->sr == 1)
			cmd->fd_1 = open(var->list->content, O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
		else if(var->dr == 1)
			cmd->fd_1 = open(var->list->content, O_RDWR | O_CREAT | O_APPEND, S_IWRITE | S_IREAD);
		else if(var->ri == 1)
			cmd->fd_0 = open(var->list->content, O_RDONLY);
	}
	else
		printf("syntax error near unexpected token `newline'"); // error
}