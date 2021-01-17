/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:32:00 by monie             #+#    #+#             */
/*   Updated: 2021/01/15 21:34:33 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_strjoin_new2(char *s1, char *s2)
{
	int len;

	len = 0;
	if (!s2)
		len = ft_strlen(s1);
	else if (!s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	return (len);
}

char	*ft_strjoin_new(char *s1, char *s2, int i, int j)
{
	char	*nstr;
	int		len;

	len = ft_strjoin_new2(s1, s2);
	if (!(nstr = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (s1)
	{
		while (s1[j])
			nstr[i++] = s1[j++];
		free(s1);
	}
	j = 0;
	if (s2)
	{
		while (s2[j])
			nstr[i++] = s2[j++];
		free(s2);
	}
	nstr[i] = '\0';
	return (nstr);
}
