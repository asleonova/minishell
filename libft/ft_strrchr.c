/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <dbliss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 19:17:30 by dbliss            #+#    #+#             */
/*   Updated: 2020/05/14 00:41:14 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;

	res = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			res = ((char*)&s[i]);
		i++;
	}
	if (res != 0)
		return (res);
	if (c == '\0')
		return ((char*)&s[i]);
	return (0);
}
