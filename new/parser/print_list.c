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

void print_list(t_commands *cmd)
{
	while(cmd->prev != NULL)
	{
		cmd = cmd->prev;
	}
	while(cmd != NULL)
	{
		printf("\nour cmd - %s\n", cmd->cmd);
		while(cmd->arg_list != NULL)
		{
			printf("our argv - %s\n", cmd->arg_list->content);
			cmd->arg_list = cmd->arg_list->next;
		}
		cmd = cmd->next;
	}
}