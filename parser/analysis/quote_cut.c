/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:24:05 by monie             #+#    #+#             */
/*   Updated: 2021/01/18 16:06:25 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_piece_one(t_var *var, char **str, char **ns, char ***env)
{
	if (var->fq == '"')
	{
		parsing_env_quote(var, *env, ns);
		shielding(var, ns, 0);
	}
}

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
			if (var->fq == '\'')
				var->not_pack = 1;
			var->j++;
		}
		else
			tmp[k++] = str[0][var->j++];
	}
	tmp[k] = '\0';
	*ns = ft_strjoin_new(*ns, tmp, 0, 0);
	create_piece_one(var, str, ns, env);
}

void	quote_cut_add(t_var *var, char ***env, char **str, char **ns)
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
		quote_cut_add(var, env, str, &ns);
		if ((str[0][var->i] == '\'' || str[0][var->i] == '"') && \
			var->oq == ' ')
			var->oq = (str[0][var->i] == '\'') ? '\'' : '"';
		else if (str[0][var->i] == var->oq || str[0][var->i + 1] == '\0')
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
