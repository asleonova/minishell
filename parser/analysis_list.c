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
	i = 0;
	int length = ft_strlen(var->list->content);
	// printf("length = %d\n", length);
	// printf("%s\t - write_cmd\n", var->list->content);
	if(!(cmd->cmd = malloc(length + 1)))
		printf("malloc error\n");
	// printf("%s\t - write_cmd\n", var->list->content);
	while(var->str[i])
	{
		cmd->cmd[i] = var->list->content[i];
		i++;
	}
	cmd->cmd[i] = '\0';
	// printf("|%s| - write_cmd_anna\n", var->list->content);
}

void	analysis_list(t_var *var, t_commands *cmd)
{
	t_commands *tmp;
	cmd_initialization(cmd);
	while(var->list != NULL)
	{
		// printf("|%s| - list\n", var->list->content);
		distribution(var->list->content, var, cmd, 0);
		if(var->r)
			processing_fd(var, cmd);
		if(cmd->end != 0)
		{
			cmd_initialization(tmp = malloc(sizeof(t_commands)));
			tmp->prev = cmd;
			cmd->next = tmp;
			cmd = tmp;
			var->exception = 0;
		}
		else if(cmd->cmd && !var->exception)
			write_argv(var, cmd);
		else if(!cmd->cmd && !var->exception)
			write_cmd(var, cmd, 0);
		if(var->list->next != NULL)
			var->list = var->list->next;
		else
			break;
	}
	var->exception = 0;
	// print_list(cmd); /* DELETE */
	// printf("fd_0\t%d\nft_1\t%d\n", cmd->fd_0, cmd->fd_1);
}