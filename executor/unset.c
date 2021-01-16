/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:13:46 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/16 18:36:29 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_data *data, t_commands *command)
{
	int valid;

	while (command->arg_lst)
	{
		valid = env_is_valid(command);
		if (ft_strchr(command->arg_lst->content, '=') == NULL && valid != FAIL)
			ft_unset_env(command->arg_lst->content, data);
		else
		{
			valid = FAIL;
			error_identifier(command, command->cmd);
		}
		next_and_clear_args(command);
	}
	if (valid == FAIL)
		return (FAIL);
	return (SUCCESS);
}
