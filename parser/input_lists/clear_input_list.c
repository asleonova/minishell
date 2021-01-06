/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_input_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:27:32 by monie             #+#    #+#             */
/*   Updated: 2021/01/06 11:48:18 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	see_input_lists(t_var *var)
{
	if (var->list)
	{
		while (var->list->prev)
			var->list = var->list->prev;
		while (var->list->next)
			var->list = var->list->next;
	}
}

void	clear_input_list(t_var *var)
{
	t_list *tmp;

	see_input_lists(var);
	if (var->list)
	{
		while (var->list->prev)
		{
			free(var->list->content);
			tmp = var->list;
			var->list = var->list->prev;
			free(tmp);
		}
		free(var->list->content);
		free(var->list);
		var->list = NULL;
	}
	free(var->str);
	var->str = NULL;
	free(var);
	var = NULL;
}
