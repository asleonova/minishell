/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 20:26:12 by monie             #+#    #+#             */
/*   Updated: 2020/12/17 19:04:07 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pass_space(t_var *var, int i)
{
	while(var->str[i] == ' ')
		i++;
	return (i);
}

int analysis_end_cmd(t_var *var)
{
	if(var->str[var->j] == '>' || var->str[var->j] == '<')
	{
		if(var->str[var->j] == '>' && var->str[var->j + 1] == '>')
			var->j += 2;
		var->j++;
		return (0);
	}
	while(var->j < var->i)
	{
		if(var->str[var->j] == '\'' && var->quote == 0)
			var->quote = 1;
		else if(var->str[var->j] == '"' && var->quote == 0)
			var->quote = 2;
		else if(var->str[var->j] == '\'' && var->quote == 1)
			var->quote = 0;
		else if(var->str[var->j] == '"' && var->quote == 2)
			var->quote = 0;
		else if(var->str[var->j] == '|')
			var->pip = 1;
		else if(var->str[var->j] == ';')
			var->semicolon = 1;
		if((var->str[var->j] == '>' || var->str[var->j] == '<' || \
			var->str[var->j] == ' ' || var->str[var->j] == '|' || \
			var->str[var->j] == ';') && var->quote == 0)
			break;
		var->j++;
	}
	return (0);
}

int analysis(t_var *var)
{
	while(var->j < var->i)
	{
		var->j = pass_space(var, var->j);
		analysis_end_cmd(var);
		var->k = pass_space(var, var->k);
		if(var->k == var->j)
			return (0);
		create_lexer(var, 0);
	}
	return (0);
}