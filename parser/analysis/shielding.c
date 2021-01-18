/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shielding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:03:34 by monie             #+#    #+#             */
/*   Updated: 2021/01/18 15:17:48 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int			shielding_utils_1(t_var *var, char **str, int i)
{
	if (str[0][i] == '\\' && str[0][i + 1] == '$')
	{
		i++;
		var->not_pack = 1;
	}
	return (i);
}

void		shielding_utils(t_var *var, char **str, char *ns, int i)
{
	int		j;

	j = 0;
	while (str[0][i])
	{
		i = shielding_utils_1(var, str, i);
		if ((str[0][i] == '\\' && str[0][i + 1] == '\\') && \
			(var->fq == ' ' || var->fq == '"'))
			i++;
		if (str[0][i] == '\\' && (str[0][i + 1] >= 33 && \
			str[0][i + 1] <= 122 ))
			i++;
		ns[j++] = str[0][i++];
	}
	ns[j] = '\0';
}

void		shielding(t_var *var, char **str, int i)
{
	char	*new_str;

	i = ft_strlen(*str);
	new_str = malloc(i + 1);
	var->np = 0;
	printf("str-> %s\n", *str);
	shielding_utils(var, str, new_str, 0);
	free(*str);
	*str = NULL;
	*str = ft_strdup(new_str);
	printf("str-> %s\n", *str);
	free(new_str);
	new_str = NULL;
}

// void		shielding_utils(t_var *var, char **str, char *ns, int i)
// {
// 	int		j;
// 	char	q;

// 	j = 0;
// 	q = ' ';
// 	while (str[0][i])
// 	{
// 		i = shielding_utils_1(var, str, i);
// 		if ((str[0][i] == '"' || str[0][i] == '\'') && \
// 			(q == ' ' || q == str[0][i]))
// 			q = str[0][i];
// 		if (str[0][i] == '\\' && (str[0][i + 1] == '\'' \
// 			|| str[0][i + 1] == '"'))
// 			i++;
// 		else if (str[0][i] == '\\' && str[0][i + 1] == '\\'
// 			&& q == ' ')
// 			i++;
// 		else if (str[0][i] == '\\' && q == ' ')
// 			i++;
// 		ns[j++] = str[0][i++];
// 	}
// 	ns[j] = '\0';
// }