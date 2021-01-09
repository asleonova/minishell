/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:56:34 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/09 12:00:26 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redirect(t_commands *command)
{
	if (command != NULL && command->cmd != NULL)
	{
		if (command->fd_0 != -1)
		{
			dup2(command->fd_0, 0);
			close(command->fd_0);
		}
		if (command->fd_1 != -1)
		{
			dup2(command->fd_1, 1);
			close(command->fd_1);
		}
	}
}

char	**ft_list_to_array(t_commands *command)
{
	char	**argv;
	int		i;
	int		count;

	i = 1;
	count = ft_lstsize(command->arg_lst);
	argv = (char**)malloc(sizeof(char *) * (count + 2));
	argv[0] = ft_strdup(command->cmd);
	while (count > 0)
	{
		argv[i++] = ft_strdup(command->arg_lst->content);
		command->arg_lst = command->arg_lst->next;
		count--;
	}
	argv[i] = 0;
	return (argv);
}

void	execute_one_func(t_commands *command, t_data *data)
{
	if (command->cmd != NULL)
	{
		cmd_identifier(command);
		if (command->command == bash)
			execute(command, data);
		else
			parse_func(command, data);
	}
}

void	executor(t_commands *command, t_data *data)
{
	int	lst_count;

	lst_count = count_list(command);
	command->save_1 = dup(1);
	command->save_0 = dup(0);
	if (lst_count == 1)
		execute_one_func(command, data);
	else
		execute(command, data);
	dup2(command->save_0, 0);
	dup2(command->save_1, 1);
	close(command->save_1);
	close(command->save_0);
}
