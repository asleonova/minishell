/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:32:36 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/11 17:36:05 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_commands *command)
{
	int flag;

	flag = 0;
	if (command->count_args == 0)
	{
		write(1, "\n", 1);
		return (SUCCESS);
	}
	while (command->arg_lst)
	{
		if (ft_strcmp("-n", command->arg_lst->content) == 0)
		{
			if (command->arg_lst->next != NULL)
				next_and_clear_args(command);
			flag = 1;
		}
		if (ft_strcmp("-n", command->arg_lst->content) != 0)
			ft_putstr_fd(command->arg_lst->content, 1);
		if (command->arg_lst->next != NULL)
			write(1, " ", 1);
		next_and_clear_args(command);
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
