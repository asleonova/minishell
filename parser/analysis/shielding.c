/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shielding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:03:34 by monie             #+#    #+#             */
/*   Updated: 2021/01/09 17:31:47 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	shielding(t_var *var, char **str, int i, int k)
{
	char	*new_str;
	
	i = ft_strlen(*str);
	new_str = malloc(i + 1);
	i = 0;
	var->np = 0;
	while(str[0][i])
	{
		if(str[0][i + 1] == '$')
			var->np = 1;
		if(str[0][i] == '\\')
			i++;
		new_str[k] = str[0][i];
		k++;
		i++;
	}
	new_str[k] = '\0';
	free(*str);
	*str = NULL;
	*str = ft_strdup(new_str);
	free(new_str);
	new_str = NULL;
}
