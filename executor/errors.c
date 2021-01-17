/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:54:59 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/17 16:37:57 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		error_path(t_commands *command)
{
	ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(command->arg_lst->content, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	g_error = 1;
	return (g_error);
}

int		error_identifier(t_commands *command, char *cmd)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": `", 1);
	ft_putstr_fd(command->arg_lst->content, 1);
	ft_putstr_fd("\' : not a valid identifier\n", 1);
	g_error = 1;
	return (g_error);
}

int		path_no_file_or_dir(t_commands *command)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(command->cmd, 1);
	ft_putstr_fd(" : No such file or directory\n", 1);
	g_error = 127;
	return (g_error);
}

int		command_not_found(char *command)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(command, 1);
	ft_putstr_fd(": command not found\n", 1);
	g_error = 127;
	return (g_error);
}

void	permission_denied(t_commands *command)
{
	if (errno != 0)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 1);
		command->fd_error = 1;
		g_error = 1;
	}
}
