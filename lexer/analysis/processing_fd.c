/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:24:30 by monie             #+#    #+#             */
/*   Updated: 2020/12/18 16:07:55 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int close_fd(int fd)
{
	close(fd);
	fd = -1;
	return(fd);
}

void processing_fd(char *str, t_syntax *syntax)
{
	if(syntax->fd_input != -1)
		syntax->fd_input = close_fd(syntax->fd_input);
	else if(syntax->fd_output != -1)
		syntax->fd_output = close_fd(syntax->fd_output);
	printf("%s - %d - %d - %d - processing_fd\n", str, syntax->ff, syntax->mf, syntax->lf);
	if(syntax->ff == 1)
	{
		syntax->fd_input = open(str, O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
		//command->redir = 1;
		//g_error = 125;
	}
	if(syntax->mf == 1)
	{
		syntax->fd_input = open(str, O_RDWR | O_CREAT | O_APPEND, S_IWRITE | S_IREAD);
		//command->redir = 1;
		//g_error = 126;
	}
	if(syntax->lf == 1)
	{
		syntax->fd_output = open(str, O_RDONLY);
		// command->back_redir = 1;
	}
	syntax->f = 0;
	printf("%d - %d\n", syntax->fd_input, syntax->fd_output);
}