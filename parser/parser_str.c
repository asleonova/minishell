/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 13:02:47 by monie             #+#    #+#             */
/*   Updated: 2020/12/20 17:34:46 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pass_space(t_var *var, int i)
{
	while(var->str[i] == ' ')
		i++;
	return (i);
}

void know_end_word(t_var *var)
{
	if(var->str[var->j] == '>' || var->str[var->j] == '<' || \
		var->str[var->j] == ';' || var->str[var->j] == '|' )
	{
		if(var->str[var->j] == '>' && var->str[var->j + 1] == '>')
			var->j += 2;
		var->j++;
		return ;
	}
	while(var->j < var->i)
	{
		if(var->str[var->j] == ' ' || var->str[var->j] == '>' || \
			var->str[var->j] == '<' || var->str[var->j] == '|' || \
			var->str[var->j] == ';')
			break;
		var->j++;
	}
}

void parser_str(t_var *var)
{
	var->i = ft_strlen(var->str);
	while(var->j < var->i)
	{
		var->j = pass_space(var, var->j);
		know_end_word(var);
		var->k = pass_space(var, var->k);
		create_lexer(var, 0);
	}
}