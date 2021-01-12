/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:03:57 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/11 19:26:09 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

static int		numeric_arg(int flag)
{
	g_error = 255;
	flag = 1;
	return(flag);
}

static int		ft_exit_errors(t_commands *command)
{
	int ret;
	int flag;

	flag = 0;
	ret = -1;
	if (command->count_args > 0)
	{
		if (ft_strcmp(command->arg_lst->content, "0") == 0)
		{
			g_error = 0;
			return (flag);
		}
		ret = ft_atoi(command->arg_lst->content);
		if (ret != 0)
			g_error = ret;
		else
			numeric_arg(flag);
	}
	if (command->count_args > 1 && g_error != 255)
	{
		g_error = 1;
		flag = 2;
	}
	return (flag);
}

int				ft_exit(t_commands *command)
{
	int flag;

	flag = ft_exit_errors(command);
	ft_putstr_fd("exit\n", 1);
	if (g_error == 255 && flag == 1)
		ft_putstr_fd("Numeric argument required\n", 1);
	else if (g_error == 1 && flag == 2)
		ft_putstr_fd("Too many arguments\n", 1);
	if (flag != 2)
		exit(g_error);
	return (g_error);
}
