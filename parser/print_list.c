/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:00:47 by monie             #+#    #+#             */
/*   Updated: 2020/12/20 17:07:04 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int print_list(t_commands *cmd)
{
	int lst_count;
	lst_count = 0;
	while(cmd->prev != NULL)
	{
		cmd = cmd->prev;
	}
	while(cmd != NULL)
	{
		//printf("\nour cmd - %s\n", cmd->cmd);
		while(cmd->arg_lst != NULL)
		{
			//printf("our argv - %s\n", cmd->arg_lst->content);
			cmd->arg_lst = cmd->arg_lst->next;
		}
		lst_count++;
		cmd = cmd->next;
	}
	return(lst_count);
}