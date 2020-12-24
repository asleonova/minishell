/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 13:29:41 by monie             #+#    #+#             */
/*   Updated: 2020/12/20 17:19:18 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_list(t_var *var)
{	
	ft_lstadd_back(&(var->list), ft_lstnew(ft_strdup(var->arr)));
}

void create_env(t_var *var)
{
	int i;

	i = 0;
	// printf("|%c|\n", var->arr[var->env_end]);
	if(!(var->env = malloc(var->env_end - var->env_start + 1)))
		g_error = 10;
	while(var->env_start < var->env_end)
	{
		var->env[i] = var->arr[var->env_start];
		i++;
		var->env_start++;
	}
	var->env[i] = '\0'; // bug
}

void	find_env(t_var *var, int i)
{
	var->env_start = -1;
	while(var->arr[i])
	{
		if(var->arr[i] == '$')
			var->env_start = i + 1;
		if(var->arr[i] == ' ' && var->env_start != -1)
			var->env_end = i;
		i++;
	}
	if(var->env_end == -1)
		var->env_end = i;
}

void	create_lexer(t_var *var, int i, char **env)
{
	var->arr = malloc(var->j - var->k + 1);
	if(var->arr == NULL)
		var->error = 1;
	while(var->k < var->j)
	{
		if(var->str[var->k] == var->q)
			var->k++;
		if(var->str[var->k] == '$')
			var->env_start = var->k;
		var->arr[i++] = var->str[var->k++];
	}
	var->arr[i] = '\0';
	if(var->env_start != -1)
	{
		find_env(var, 0);
		create_env(var);
		(void)env;
		parsing_env(var, env, &var->env);
	}
	var->env_start = -1;
	var->env_end = -1;
	create_list(var);
	free(var->arr);
	var->arr = NULL;
}