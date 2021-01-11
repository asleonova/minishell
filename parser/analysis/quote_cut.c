/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:24:05 by monie             #+#    #+#             */
/*   Updated: 2021/01/11 14:28:27 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	quote_cut_utils(t_var *var, char **str, int i, int k)
// {
	
// }

void	quote_cut(t_var *var, char **str, int i, int k)
{
	char *new_str;

	i = ft_strlen(*str);
	new_str = malloc(i);
	i = 0;
	while (str[0][i])
	{
		if ((str[0][i] == '\'' || str[0][i] == '"') && \
			str[0][i -1] != '\\')
		{
			if (var->oq != '\'' && var->oq != '"')
				var->oq = (str[0][i] == '\'') ? '\'' : '"';
			if (var->oq == str[0][i])
				i++;
		}
		if (str[0][i] == '\\' && str[0][i + 1] == '"' && \
			str[0][i + 1] == '"')
			i++;
		else if (str[0][i] == '\\' && str[0][i + 1] <= 33)
			i++;
		new_str[k++] = str[0][i++];
	}
	new_str[k] = '\0';
	free(*str);
	*str = NULL;
	*str = ft_strdup(new_str);
	free(new_str);
	new_str = NULL;
}