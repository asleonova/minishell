/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 14:10:16 by monie             #+#    #+#             */
/*   Updated: 2020/12/20 17:41:35 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_argv(t_var *var, t_commands *cmd)
{
	ft_lstadd_back(&(cmd->arg_lst), ft_lstnew(ft_strdup(var->list->content)));
}

void	write_cmd(t_var *var, t_commands *cmd, int i)
{
	cmd->cmd = malloc(ft_strlen(var->list->content) + 1);
	if(cmd->cmd == NULL)
		var->error = 2;
	while(var->str[i])
	{
		cmd->cmd[i] = var->list->content[i];
		i++;
	}
	cmd->cmd[i] = '\0';
}

void	analysis_list(t_var *var, t_commands *cmd)
{
	t_commands *tmp;
	//cmd = malloc(sizeof(t_commands));
	cmd_initialization(cmd);
	while(var->list != NULL)
	{
		if(var->list->content[0]== ';')
		{
			cmd_initialization(tmp = malloc(sizeof(t_commands)));
			if(var->list->next != NULL)
				var->list = var->list->next;
			tmp->prev = cmd;
			cmd->next = tmp;
			cmd = tmp;
		}
		if(cmd->cmd)
			write_argv(var, cmd);
		if(!cmd->cmd)
			write_cmd(var, cmd, 0);
		var->list = var->list->next;
	}
	print_list(cmd); /* DELETE */
}