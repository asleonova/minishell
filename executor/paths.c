/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:08:01 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/11 18:08:28 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		**get_paths(t_data *data)
{
	char	*path;
	char	**paths;

	path = get_env_values(data, "PATH");
	paths = ft_split(path, ':');
	free(path);
	return (paths);
}

void		add_path_to_commands(t_commands *command, t_data *data)
{
	char		**paths;
	char		*join;
	char		*cmd;
	int			i;
	struct stat	buf;

	i = 0;
	cmd = NULL;
	paths = get_paths(data);
	while (paths[i])
	{
		join = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(join, command->cmd);
		free(join);
		if (stat(cmd, &buf) == 0)
			break ;
		i++;
	}
	free_tab(paths);
	command->cmd = cmd;
	free(cmd);
}

int			path_exist(t_commands *command, t_data *data)
{
	int		i;
	int		found;

	i = -1;
	found = 0;
	while (data->envp[++i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
		{
			found = 1;
			break ;
		}
	}
	if (data->envp[i] == NULL && command->command != bash)
		path_no_file_or_dir(command);
	return (found);
}

void		path_does_not_exist(t_commands *command, t_data *data)
{
	if (!path_exist(command, data) && (ft_strchr(command->cmd, '/') == NULL))
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(command->cmd, 1);
		ft_putstr_fd(" : No such file or directory\n", 1);
		g_error = 127;
		exit(g_error);
	}		
}
