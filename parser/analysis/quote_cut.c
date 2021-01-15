/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:24:05 by monie             #+#    #+#             */
/*   Updated: 2021/01/15 21:32:28 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_piece(t_var *var, char **str, char **ns)
{
	char	*tmp;
	char	*temp;
	int		k;
	
	k = 0;
	tmp = malloc(var->i - var->j + 1);
	while(var->j < var->i)
	{
		tmp[k++] = str[0][var->j++];
	}
	tmp[k] = '\0';
	printf("tmp-> %s\n", tmp);
	temp = ft_strjoin_new(*ns, tmp, 0, 0);
	printf("temp-> %s\n", temp);
}

void	quote_cut(t_var *var, char **str, int i)
{
	char *ns;
	ns = NULL;
	(void)i;
	var->i = 0;
	var->j = 0;
	while(str[0][var->i])
	{
		if(str[0][var->i] == '\'' || str[0][var->i] == '"')
		{
			if(var->i > 0)
				create_piece(var, str, &ns);
			break;
		}
		var->i++;
	}
	var->j = var->i;
	while(str[0][var->i])
	{
		if((str[0][var->i] == '\'' || str[0][var->i] == '"') && \
			var->oq == ' ')
			var->oq = (str[0][var->i] == '\'') ? '\'' : '"';
		else if(str[0][var->i] == var->oq)	
		{
			var->i++;
			create_piece(var, str, &ns);
		}
		var->i++;
	}
}

//alias mm="make && ./minishell"