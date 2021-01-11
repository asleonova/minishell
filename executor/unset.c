/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:13:46 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/11 17:42:38 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_data *data, t_commands *command)
{
	while (command->arg_lst)
	{
		if (ft_strchr(command->arg_lst->content, '=') == NULL)
			ft_unset_env(command->arg_lst->content, data);
		else
			error_identifier(command);
		next_and_clear_args(command);
	}
	return (SUCCESS);
}
