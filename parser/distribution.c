/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 18:06:18 by monie             #+#    #+#             */
/*   Updated: 2020/12/22 18:48:06 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	distribution_initialization(t_var *var)
{
	var->r = 0;
	var->sr = 0;
	var->dr = 0;
	var->ri = 0;
	var->env = 0;
}

void	distribution(char *str, t_var *var, t_commands *cmd, int i)
{
	distribution_initialization(var);
	if(str[i] == '|' || str[i] == ';')
	{
		cmd->end = (str[i] == '|') ? 1 : 2;
		var->exception = 1;
	}	
	// else if(str[i] == '$')
	// 	var->env = 1;
	else if(str[i] == '>' && str[i + 1] == '>')
		var->dr = 1;
	else if(str[i] == '>')
		var->sr = 1;
	else if(str[i] == '<')
		var->ri = 1;
	if(var->sr == 1 || var->dr == 1 || var->ri == 1)
	{
		var->r = 1;
		var->exception = 1;
	}
}