/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:56:43 by monie             #+#    #+#             */
/*   Updated: 2021/01/11 18:16:08 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_str(char *str, char **content, int i)
{
	int	j;

	free(*content);
	*content = NULL;
	j = ft_strlen(str);
	while (str[i] != '=')
	{
		i++;
	}
	*content = malloc(j - i + 1);
	j = 0;
	while (str[i++])
		(*content)[j++] = str[i];
	(*content)[j] = '\0';
}

int		search_str(char *str, char *my_env, int k)
{
	int	i;

	i = 0;
	while (my_env[k])
	{
		if (my_env[k] == str[i])
		{
			k++;
			i++;
		}
		else if (my_env[k] != str[i])
			return (1);
	}
	if (str[i] == '=')
	{
		k++;
		return (0);
	}
	return (1);
}

void	parsing_question(char **str)
{
	free(*str);
	*str = NULL;
	*str = ft_itoa(g_error);
}

void	parsing_env(t_var *var, char **env, char **str)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	if (str[0][1] == '?' && (str[0][2] == ' ' || \
		str[0][2] == '\0'))
		parsing_question(str);
	else
	{
		while (env[i])
		{
			if (!search_str(env[i], *str, 1))
			{
				create_str(env[i], str, 0);
				var->envf = 1;
			}
			i++;
		}
	}
}
