/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:31:25 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/09 11:32:24 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_list(t_commands *cmd)
{
	int lst_count;

	lst_count = 0;
	while (cmd->prev != NULL)
	{
		cmd = cmd->prev;
	}
	while (cmd != NULL)
	{
		lst_count++;
		cmd = cmd->next;
	}
	return (lst_count);
}
