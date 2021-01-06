/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 19:02:33 by dbliss            #+#    #+#             */
/*   Updated: 2020/12/24 15:51:37 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*begin;

	begin = NULL;
	if (!(begin = malloc(sizeof(t_list))))
		return (0);
	if (begin)
	{
		begin->content = content;
		begin->next = NULL;
		begin->prev = NULL;
	}
	return (begin);
}
