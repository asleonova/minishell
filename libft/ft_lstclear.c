/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <dbliss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 12:28:50 by dbliss            #+#    #+#             */
/*   Updated: 2020/05/16 11:28:26 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *temp;

	if (lst)
	{
		while (*lst)
		{
			if (del)
			{
				del((*lst)->content);
			}
			temp = (*lst)->next;
			*lst = temp;
			free(*lst);
		}
		*lst = NULL;
	}
}
