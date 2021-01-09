/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shielding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:03:34 by monie             #+#    #+#             */
/*   Updated: 2021/01/09 19:01:15 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	shielding_utils(t_var *var, char **ns, char **str, int k)
{
	int q;
	int i;

	i = 0;
	q = 0;
	if (str[0][i] == '"')
	{
		q++;
		if (q == 2)
			q = 0;
	}
	if (str[0][i + 1] == '$' && q == 0)
		var->np = 1;
	if (str[0][i] == '\\' && q == 0)
		i++;
	ns[0][k] = str[0][i];
	k++;
	i++;
}

void	shielding(t_var *var, char **str, int i, int k)
{
	char	*new_str;

	i = ft_strlen(*str);
	new_str = malloc(i + 1);
	var->np = 0;
	while (str[0][i])
	{
		shielding_utils(var, &new_str, str, k);
	}
	new_str[k] = '\0';
	free(*str);
	*str = NULL;
	*str = ft_strdup(new_str);
	free(new_str);
	new_str = NULL;
}
