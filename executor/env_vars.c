/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:51:27 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/11 17:55:26 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*get_env_values(t_data *data, char *key)
{
	int		i;
	char	**tmp;
	char	*value;

	i = -1;
	value = NULL;
	while (data->envp[++i])
	{
		tmp = ft_split(data->envp[i], '=');
		if (ft_strcmp(tmp[0], key) == 0)
		{
			if (tmp[1] == NULL)
				value = ft_strdup(" ");
			else
				value = ft_strdup(tmp[1]);
			free_tab(tmp);
			break ;
		}
		free_tab(tmp);
	}
	return (value);
}

void		add_env_var(char *var, t_data *data)
{
	char	**tmp;
	int		i;
	int		len;

	len = tab_len(data->envp);
	i = 0;
	tmp = (char**)malloc(sizeof(char *) * (len + 2));
	while (i < len)
	{
		tmp[i] = ft_strdup(data->envp[i]);
		i++;
	}
	tmp[i] = ft_strdup(var);
	tmp[i + 1] = 0;
	free_tab(data->envp);
	data->envp = tmp;
}

void		delete_env_var(char *var, t_data *data)
{
	char	**tmp;
	char	**split;
	int		i;
	int		len;
	int		j;

	len = tab_len(data->envp);
	i = -1;
	j = 0;
	tmp = (char**)malloc(sizeof(char *) * len);
	while (++i < len)
	{
		split = ft_split(data->envp[i], '=');
		if (ft_strcmp(split[0], var) == 0)
			free_tab(split);
		else
		{
			free_tab(split);
			tmp[j++] = ft_strdup(data->envp[i]);
		}
	}
	tmp[j] = 0;
	free_tab(data->envp);
	data->envp = tmp;
}

void		change_env_values(char *var, t_data *data)
{
	char	*cwd;
	char	**temp;
	char	*tmp;

	temp = ft_split(var, '=');
	ft_unset_env(temp[0], data);
	free_tab(temp);
	tmp = getcwd(NULL, 0);
	cwd = ft_strjoin(var, tmp);
	free(tmp);
	add_env_var(cwd, data);
	free(cwd);
}
