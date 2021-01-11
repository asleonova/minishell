/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:24:05 by monie             #+#    #+#             */
/*   Updated: 2021/01/11 16:32:55 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		cut_util(t_var *var, char **str, int i)
{
	if ((str[0][i] == '\'' || str[0][i] == '"') && \
		str[0][i - 1] != '\\')
	{
		if (var->oq != '\'' && var->oq != '"')
			var->oq = (str[0][i] == '\'') ? '\'' : '"';
		if (var->oq == str[0][i])
			i++;
	}
	return (i);
}

void	quote_cut_loop(t_var *var, char **str, char *ns, int i)
{
	int k;

	k = 0;
	while (str[0][i])
	{
		if (str[0][i] == '"' && str[0][i + 1] == '\\' && \
			str[0][i + 2] == '\\' && str[0][i + 3] == '"')
		{
			i++;
			ns[k++] = str[0][i++];
			i += 2;
		}
		i = cut_util(var, str, i);
		if (str[0][i] == '\\' && str[0][i + 1] == '"' && \
			str[0][i + 1] == '"')
			i++;
		else if (str[0][i] == '\\' && str[0][i + 1] <= 33)
			i++;
		ns[k++] = str[0][i++];
	}
	ns[k] = '\0';
}

void	quote_cut(t_var *var, char **str, int i)
{
	char *new_str;

	i = ft_strlen(*str);
	new_str = malloc(i);
	quote_cut_loop(var, str, new_str, 0);
	free(*str);
	*str = NULL;
	*str = ft_strdup(new_str);
	free(new_str);
	new_str = NULL;
}
