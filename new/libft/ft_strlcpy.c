/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <dbliss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 23:39:14 by dbliss            #+#    #+#             */
/*   Updated: 2020/05/14 00:51:44 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	size;

	size = 0;
	while (src[size])
		size++;
	if (dstsize == 0)
		return (size);
	size = 0;
	while (src[size] && size < dstsize - 1)
	{
		dst[size] = src[size];
		size++;
	}
	dst[size] = '\0';
	size = 0;
	while (src[size])
		size++;
	return (size);
}
