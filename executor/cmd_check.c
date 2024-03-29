/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:14:34 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/11 19:16:26 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_commands	*cmd_check(t_commands *cmd, t_data *data)
{
	if (cmd->cmd == NULL && (cmd->fd_1 != -1 || cmd->fd_0 != -1))
	{
		if (cmd->next != NULL)
			cmd = cmd->next;
	}
	if (cmd != NULL && cmd->cmd != NULL && cmd->fd_error != 1)
	{
		cmd_identifier(cmd);
		if ((cmd->count_args > 0 && cmd->command == export) ||
				cmd->command == unset || cmd->command == cd)
		{
			parse_func(cmd, data);
			cmd = cmd->next;
		}
	}
	return (cmd);
}
