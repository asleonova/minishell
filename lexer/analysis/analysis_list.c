/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 15:32:58 by monie             #+#    #+#             */
/*   Updated: 2020/12/18 19:53:22 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_syntax(t_syntax *syntax)
{
	syntax->f = 0; /* >  >> <*/
	syntax->mf = 0;	/* > */
	syntax->lf = 0;	/* < */
	syntax->ff = 0;	/* >> */
	syntax->pf = 0; /* | */
	syntax->envf = 0;
	syntax->fd_input = -1;
	syntax->fd_output = -1;
	syntax->cmdf = 0;
}

int		write_argv(char *str, t_commands *cmd)
{
	ft_lstadd_back(&(cmd->lst), ft_lstnew(ft_strdup(str)));
	return (0);
}

int		write_cmd(char *str, t_syntax *syntax, t_commands *cmd, int i)
{
	cmd->cmd = malloc(ft_strlen(str) + 1);
	if(cmd->cmd == NULL)
		syntax->ef = 1;
	while(str[i])
	{
		cmd->cmd[i] = str[i];
		i++;
	}
	cmd->cmd[i] = '\0';
	syntax->cmdf = 1;
	return (0);
}

int		analysis_list(t_var *var, char ***env)
{
	t_syntax syntax;
	t_commands *cmd;
	

	cmd = malloc(sizeof(t_commands));
	init_syntax(&syntax);
	t_list *tmp = var->list;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		if (!distribution(tmp->content, &syntax, 0) && syntax.f == 0)
		{
			if (syntax.envf)
				parsing_env(env, &tmp->content);
			if (syntax.f == 0 && syntax.cmdf == 0)
				write_cmd(tmp->content, &syntax, cmd, 0);	
			else if (syntax.cmdf == 1 && syntax.f == 0)
				write_argv(tmp->content, cmd);	
		}
		if (syntax.f == 1 && !(tmp->next == NULL))
		{
			tmp=tmp->next;
			processing_fd(tmp->content, &syntax);
			syntax.f = 0;
		}
		tmp = tmp->next;
	}
	printf("our cmd: %s\n", cmd->cmd);
	tmp = cmd->lst;
	while(tmp != NULL)
	{
	 	printf("we see: %s\n", tmp->content);
		tmp = tmp->next;
	}
	if(syntax.ef == 1)
		return(1);
	return(0);
}