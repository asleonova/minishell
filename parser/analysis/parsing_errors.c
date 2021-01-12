/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:54:33 by monie             #+#    #+#             */
/*   Updated: 2021/01/12 19:44:55 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	syntax_error(t_var *var, t_commands *cmd)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 1);
	
	cmd->invalid = 1;
	var->list = var->list->next;
	if(var->list->next)
		var->list = var->list->next;
	g_error = 258;
}
