/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:55:41 by monie             #+#    #+#             */
/*   Updated: 2020/12/20 17:48:09 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void intro(void)
{
	write(1, "minishell: ", 11);
}

int done(t_var *var)
{
	if(!(ft_strncmp(var->str, "exit", 4)))
		return (0);
 	return (1);
}

void		copy_env(char **envp, t_data *data)
{
	int		len;
	int		i;

	i = 0;
	len = tab_len(envp);
	data->envp = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp[i] = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_var	var;
	t_commands cmd;
	t_data	data;
	int 	i;
	
	i = 1;
	argc = 0;
	argv = NULL;
	copy_env(envp, &data);
	//cmd = malloc(sizeof(t_commands));
	while(i)
	{
		var_initialization(&var);
		intro();
		get_next_line(0, &var.str);
		parser_str(&var);
		/* здесь буддет готовые листы полученные из строки */
		analysis_list(&var, &cmd);
		/* Анены функции */
		executor(&cmd, &data);
		i = done(&var);
		var_clear(&var);
		// free(cmd);
		// cmd = NULL;
	}
	if(!i)
		write(1, "Error program", 14);
	return(0);
}