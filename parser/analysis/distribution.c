/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:56:24 by monie             #+#    #+#             */
/*   Updated: 2021/01/11 16:07:36 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	distribution_initialization(t_var *var)
{
	var->r = 0;
	var->env = 0;
	var->exception = 0;
	var->shielding = 0;
}

int		distribution(char *str, t_var *var, t_commands *cmd, int i)
{
	distribution_initialization(var);
	if (str[i] == '|' || str[i] == ';')
	{
		cmd->end = (str[i] == '|') ? 1 : 2;
		var->exception = 1;
	}
	else if (str[i] == '>' && str[i + 1] == '>')
		var->r = 2;
	else if (str[i] == '>')
		var->r = 1;
	else if (str[i] == '<')
		var->r = 3;
	while (var->str[i])
	{
		if (var->str[i] == '"' || var->str[i] == '\'')
			var->q = (var->str[i] == '\'') ? 1 : 2;
		if (var->str[i] == '\\')
			var->shielding = 1;
		i++;
	}
	if (var->r || cmd->end || var->q || var->shielding)
		return (1);
	return (0);
}
