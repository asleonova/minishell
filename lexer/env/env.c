/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:47:55 by monie             #+#    #+#             */
/*   Updated: 2020/12/17 15:38:34 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int create_str(char *str, char **content, int i)
{
	int j;
	
	free(*content);
	*content = NULL;
	j = ft_strlen(str);
	while(str[i] != '=')
	{
		i++;
	}
	*content = malloc(j - i +1);
	if(*content == NULL)
		return(1);
	j = 0;
	while(str[i++])
	{
		(*content)[j++] = str[i];
	}
	(*content)[j] = '\0';
	return (0);
}

int search_str(char *str, char *my_env, int k)
{
	int i;

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
		return(0);
	}
	return (1);
}

void parsing_env(char ***env, char **str)
{
	int j;
	int i;
	
	i = 0;
	j = 0;
	while(env[0][i])
	{
		if(!search_str(env[0][i], *str, 1))
			create_str(env[0][i], str, 0);
		i++;
	}
}