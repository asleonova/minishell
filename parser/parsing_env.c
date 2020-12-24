/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:27:35 by monie             #+#    #+#             */
/*   Updated: 2020/12/22 22:57:36 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_str(char *str, char **content, int i)
{
	int	j;
	
	free(*content);
	*content = NULL;
	j = ft_strlen(str);
	while(str[i] != '=')
	{
		i++;
	}
	*content = malloc(j - i +1);
	if(*content == NULL)
		g_error = 10;
	j = 0;
	while(str[i++])
	{
		(*content)[j++] = str[i];
	}
	(*content)[j] = '\0';
}

int		search_str(char *str, char *my_env, int k)
{
	int	i;

	i = 0;
	while(my_env[k])
	{
		if(my_env[k] == str[i])
		{
			k++;
			i++;
		}
		else if(my_env[k] != str[i])
			return (1);
	}
	if(str[i] == '=')
	{
		k++;
		return (0);
	}
	return (1);
}

void	replices_arr()
{
	
}

void	parsing_env(t_var *var, char **env, char **str)
{
	int	j;
	int	i;
	
	i = 0;
	j = 0;
	while(env[i])
	{
		if(!search_str(env[i], *str, 0))
			create_str(env[i], str, 0);
		i++;
	}
	if(!var->q) // исправить на одинарные и если без кавычек
	{
		free(var->arr);
		var->arr = NULL;
		var->arr = ft_strdup(var->env);
		free(var->env);
		var->env = NULL;
	}
}