/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:03:57 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/09 12:05:42 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		ft_exit_errors(t_commands *command)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	if (command->count_args > 0)
	{
		while (command->arg_lst->content[++i])
			if (!(ft_isalnum(command->arg_lst->content[++i])))
			{
				g_error = 255;
				flag = 1;
			}
		if (command->count_args > 1 && g_error != 255)
		{
			g_error = 1;
			flag = 1;
		}
		if (g_error != 1 && g_error != 255)
			g_error = ft_atoi(command->arg_lst->content);
	}
	ft_putstr_fd("exit\n", 1);
	if (g_error == 255 && flag == 1)
		ft_putstr_fd("Numeric argument required\n", 1);
	else if (g_error == 1 && flag == 1)
		ft_putstr_fd("Too many arguments\n", 1);
}

void	ft_exit(t_commands *command)
{
	printf("G_ERROR: %d\n", g_error);
	ft_exit_errors(command);
	exit(g_error);
}
