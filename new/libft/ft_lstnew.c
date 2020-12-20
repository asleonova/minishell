/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <dbliss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 19:02:33 by dbliss            #+#    #+#             */
/*   Updated: 2020/05/16 00:00:58 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*begin;

	begin = NULL;
	if (!(begin = malloc(sizeof(t_list))))
		return (0);
	if (begin)
	{
		begin->content = content;
		begin->next = NULL;
	}
	return (begin);
}
