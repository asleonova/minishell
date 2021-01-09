/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 23:34:31 by monie             #+#    #+#             */
/*   Updated: 2021/01/09 19:04:52 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unpacking_env(t_env *tmp, char **str, int j)
{
	tmp->str = malloc(ft_strlen(tmp->env) + ft_strlen(*str) + 1);
	while (str[0][tmp->i])
	{
		if ((str[0][tmp->i]) == '$' && j)
		{
			j--;
			while (tmp->env[tmp->k])
				tmp->str[tmp->j++] = tmp->env[tmp->k++];
			tmp->i = tmp->end + 1;
		}
		if (str[0][tmp->i] != '"')
			tmp->str[tmp->j++] = str[0][tmp->i++];
		else
			tmp->i++;
	}
	tmp->str[tmp->j] = '\0';
	free(*str);
	*str = NULL;
	*str = strdup(tmp->str);
	free(tmp->str);
	tmp->str = NULL;
	free(tmp->env);
	tmp->env = NULL;
}

void	search_env(t_env *tmp, char **str)
{
	while (str[0][tmp->i] != '$' && str[0][tmp->i])
		tmp->i++;
	tmp->j = tmp->i;
	if (str[0][tmp->i + 1] >= 'A' && str[0][tmp->i + 1] <= 'Z')
	{
		tmp->i++;
		while (str[0][tmp->i] >= 'A' && str[0][tmp->i] <= 'Z')
		{
			if (str[0][tmp->i + 1] >= 'A' && str[0][tmp->i + 1] <= 'Z')
				tmp->i++;
			else
				break ;
		}
	}
}

void	count_dollar(t_env *tmp, char **str)
{
	int i;

	i = 0;
	tmp->dollar = 0;
	while (str[0][i])
	{
		if (str[0][i] == '$')
			tmp->dollar++;
		i++;
	}
}

void	parsing_env_quote(t_var *var, char **env, char **str)
{
	t_env *tmp;

	tmp = malloc(sizeof(t_env));
	count_dollar(tmp, str);
	while (tmp->dollar)
	{
		env_initialization(tmp);
		search_env(tmp, str);
		tmp->env = malloc(tmp->i - tmp->j + 1);
		while (tmp->j <= tmp->i)
			tmp->env[tmp->k++] = str[0][tmp->j++];
		tmp->env[tmp->k] = '\0';
		parsing_env(var, env, &tmp->env);
		env_initialization_step(tmp);
		unpacking_env(tmp, str, 1);
		tmp->dollar--;
	}
	free(tmp);
	tmp = NULL;
}
