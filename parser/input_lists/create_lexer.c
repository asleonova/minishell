/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 13:29:41 by monie             #+#    #+#             */
/*   Updated: 2021/01/09 18:32:37 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_list(t_var *var)
{
	ft_lstadd_back(&(var->list), ft_lstnew(ft_strdup(var->arr)));
	free(var->arr);
	var->arr = NULL;
}

void	create_lexer(t_var *var, int i)
{
	var->arr = malloc(var->j - var->k + 1);
	if (var->arr == NULL)
		var->error = 1;
	while (var->k < var->j)
	{
		if (var->str[var->k] == '\\')
		{
			var->arr[i++] = var->str[var->k++];
			var->arr[i++] = var->str[var->k++];
		}
		else
			var->arr[i++] = var->str[var->k++];
	}
	var->arr[i] = '\0';
	printf("var->arr\t%s\n", var->arr);
	create_list(var);
}
