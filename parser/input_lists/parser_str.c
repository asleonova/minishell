/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 13:02:47 by monie             #+#    #+#             */
/*   Updated: 2021/01/02 12:51:33 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		pass_space(t_var *var, int i)
{
	while (var->str[i] == ' ')
		i++;
	return (i);
}

void	parser_quotes(t_var *var, char c)
{
	var->q = c;
	while (var->j < var->i)
	{
		var->j++;
		if (var->str[var->j] == c)
			return ;
	}
}

void	know_end_word(t_var *var)
{
	if (var->str[var->j] == '>' || var->str[var->j] == '<' || \
		var->str[var->j] == ';' || var->str[var->j] == '|')
	{
		if (var->str[var->j] == '>' && var->str[var->j + 1] == '>')
			var->j++;
		var->j++;
		return ;
	}
	while (var->j < var->i)
	{
		if (var->str[var->j] == '\'' || var->str[var->j] == '"')
			parser_quotes(var, var->str[var->j]);
		if (var->str[var->j] == ' ' || var->str[var->j] == '>' || \
			var->str[var->j] == '<' || var->str[var->j] == '|' || \
			var->str[var->j] == ';')
			break ;
		var->j++;
	}
}

void	parser_str(t_var *var)
{
	var->i = ft_strlen(var->str);
	while (var->j < var->i)
	{
		var->j = pass_space(var, var->j);
		know_end_word(var);
		var->k = pass_space(var, var->k);
		if (var->k != var->j)
			create_lexer(var, 0);
	}
}
