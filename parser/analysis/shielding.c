/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shielding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:03:34 by monie             #+#    #+#             */
/*   Updated: 2021/01/11 14:26:14 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	shielding_utils(char **str, char *ns, int i, int j)
{
	char q;

	q = ' ';
	while (str[0][i])
	{
		if ((str[0][i] == '"' || str[0][i] == '\'') && \
			(q == ' ' || q == str[0][i]))
			q = str[0][i];
		if (str[0][i] == '\\' && (str[0][i + 1] == '\'' \
			|| str[0][i + 1] == '"'))
			ns[j++] = str[0][i++];
		else if (str[0][i] == '\\' && str[0][i + 1] == '\\'
			&& q == ' ')
			i++;
		else if (str[0][i] == '\\' && q == ' ')
			i++;
		ns[j++] = str[0][i++];
	}
	ns[j] = '\0';
}

void	shielding(t_var *var, char **str, int i)
{
	char	*new_str;

	i = ft_strlen(*str);
	new_str = malloc(i + 1);
	var->np = 0;
	shielding_utils(str, new_str, 0, 0);
	free(*str);
	*str = NULL;
	*str = ft_strdup(new_str);
	free(new_str);
	new_str = NULL;
}
