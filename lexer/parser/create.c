/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:47:14 by monie             #+#    #+#             */
/*   Updated: 2020/12/17 19:15:52 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int create_list(t_var *var)
{	
	ft_lstadd_back(&(var->list), ft_lstnew(ft_strdup(var->arr)));
	return (0);
}

int create_lexer(t_var *var, int i)
{
	int quote;

	quote = 0;
	var->arr = malloc(var->j - var->k + 1);
	if(var->arr == NULL)
		var->error = 1;
	while(var->k < var->j)
	{
		var->arr[i++] = var->str[var->k++];
	}
	var->arr[i] = '\0';
	create_list(var);
	var->ef = 0;
	free(var->arr);
	var->arr = NULL;
	return (0);
}