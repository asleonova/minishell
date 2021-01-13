/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:54:33 by monie             #+#    #+#             */
/*   Updated: 2021/01/12 20:21:33 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	syntax_error(t_var *var)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 1);
	var->invalid = 1;
	var->list = var->list->next;
	if (var->list->next)
		var->list = var->list->next;
	g_error = 258;
}
