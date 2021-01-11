/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:00:53 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/11 17:44:48 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_print_export(t_data *data)
{
	int		i;
	char	**split;
	char	*var;

	i = 0;
	ft_sort_list(data);
	while (data->envp[i])
	{
		var = ft_strchr(data->envp[i], '=');
		split = ft_split(data->envp[i], '=');
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(split[0], 1);
		if (var)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			if (split[1])
				ft_putstr_fd(split[1], 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		free_tab(split);
		i++;
	}
}

void			ft_unset_env(char *str, t_data *data)
{
	char	*tmp;

	if ((tmp = get_env_values(data, str)) != NULL)
	{
		free(tmp);
		delete_env_var(str, data);
	}
}

void			ft_export_update(t_data *data, char *str)
{
	char	**temp;

	temp = ft_split(str, '=');
	ft_unset_env(temp[0], data);
	free_tab(temp);
	add_env_var(str, data);
}

int				ft_export(t_data *data, t_commands *command)
{
	while (command->arg_lst)
	{
		ft_export_update(data, command->arg_lst->content);
		next_and_clear_args(command);
	}
	return (SUCCESS);
}