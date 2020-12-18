/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:57:57 by monie             #+#    #+#             */
/*   Updated: 2020/11/26 17:00:44 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_mod(const char *str, size_t n)
{
	char	*res;
	char	*check_mem;

	check_mem = malloc(n * sizeof(char) + 1);
	if (!(check_mem))
		return (NULL);
	res = check_mem;
	while (n-- > 0)
	{
		*check_mem++ = *(char*)str++;
	}
	*check_mem = '\0';
	return (res);
}
