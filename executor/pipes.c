/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:15:29 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/09 12:21:40 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			execute_execve(t_commands *command, t_data *data)
{
	char	**argv;

	if (ft_strchr(command->cmd, '/') != NULL)
	{
		argv = ft_list_to_array(command);
		if (execve(argv[0], argv, data->envp) == -1)
		{
			command_not_found(argv[0]);
			exit(g_error);
		}
	}
	else
	{
		add_path_to_commands(command, data);
		argv = ft_list_to_array(command);
		if (execve(argv[0], argv, data->envp) == -1)
		{
			command_not_found(argv[0]);
			exit(g_error);
		}
	}
	free(argv);
	return (g_error);
}

void		execute(t_commands *command, t_data *data)
{
	pid_t	pid;
	int		pfd[2];

	if (command != NULL && command->cmd != NULL)
	{
		pipe(pfd);
		pid = fork();
		if (pid == -1)
		{
			strerror(pid);
			exit(errno);
		}
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			path_does_not_exist(command, data);
			exec_first_command(command, data, pfd);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			wait(&pid);
			g_error = WEXITSTATUS(pid);
			check_pipe(data, command, pfd);
		}
	}
}

int		exec_first_command(t_commands *command, t_data *data, int pfd[2])
{
	if (command != NULL && command->cmd != NULL)
	{
		if (command->end == 1)
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
		}
		check_redirect(command);
		cmd_identifier(command);
		if (command->command == bash)
			execute_execve(command, data);
		else
		{
			parse_func(command, data);
			exit(g_error);
		}
	}
	return (0);
}

int		check_pipe(t_data *data, t_commands *command, int pfd[2])
{
	if (command->next != NULL && command->next->cmd != NULL)
	{
		if (command->end != 2)
		{
			close(pfd[1]);
			dup2(pfd[0], 0);
			execute(command->next, data);
		}
		else
			execute(command->next, data);
	}
	return (0);
}
