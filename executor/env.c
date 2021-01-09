/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:38:45 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/09 11:51:03 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_commands *command, t_data *data)
{
	int i;

	i = 0;
	if (!path_exist(command, data))
		return (g_error);
	while (data->envp[i])
	{
		if (ft_strchr(data->envp[i], '=') != NULL)
		{
			ft_putstr_fd(data->envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (SUCCESS);
}
