/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:24:05 by monie             #+#    #+#             */
/*   Updated: 2021/01/16 18:08:14 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_piece(t_var *var, char **str, char **ns, char ***env)
{
	char	*tmp;
	int		k;

	k = 0;
	var->fq = ' ';
	tmp = malloc(var->i - var->j + 1);
	while (var->j < var->i)
	{
		if ((str[0][var->j] == '\'' || str[0][var->j] == '"') && \
			(var->fq == ' ' || var->fq == str[0][var->j]))
		{
			if (var->fq == ' ')
				var->fq = (str[0][var->j] == '\'') ? '\'' : '"';
			var->j++;
		}
		else
			tmp[k++] = str[0][var->j++];
	}
	tmp[k] = '\0';
	*ns = ft_strjoin_new(*ns, tmp, 0, 0);
	if (var->fq == '"')
	{
		parsing_env_quote(var, *env, ns);
		shielding(var, ns, 0);
	}
}

void	q(t_var *var, char ***env, char **str, char **ns)
{
	if ((str[0][var->i] == '\'' || str[0][var->i] == '"') && \
		var->oq == ' ')
	{
		if (var->i != var->j)
			create_piece(var, str, ns, env);
	}
}

void	quote_cut(t_var *var, char **str, char ***env)
{
	char *ns;

	ns = NULL;
	var->i = 0;
	var->j = 0;
	while (str[0][var->i])
	{
		q(var, env, str, &ns);
		if ((str[0][var->i] == '\'' || str[0][var->i] == '"') && \
			var->oq == ' ')
			var->oq = (str[0][var->i] == '\'') ? '\'' : '"';
		else if (str[0][var->i] == var->oq)
		{
			var->i++;
			var->oq = ' ';
			create_piece(var, str, &ns, env);
			var->j = var->i;
			continue ;
		}
		var->i++;
	}
	free(*str);
	*str = ns;
}
