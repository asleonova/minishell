/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:21:30 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/09 11:24:10 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_commands *command, t_data *data)
{
	char	*cwd;
	int		status;

	if (command->count_args == 0)
	{
		change_env_values("OLDPWD=", data);
		cwd = get_env_values(data, "HOME");
		chdir(cwd);
		free(cwd);
		cwd = getcwd(NULL, 0);
		change_env_values("PWD=", data);
	}
	else
	{
		change_env_values("OLDPWD=", data);
		status = chdir(command->arg_lst->content);
		if (status < 0)
			error_path(command);
		else
		{
			cwd = getcwd(NULL, 0);
			change_env_values("PWD=", data);
		}
	}
	return (SUCCESS);
}
