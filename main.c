/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:55:41 by monie             #+#    #+#             */
/*   Updated: 2021/01/11 19:13:01 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	intro(void)
{
	write(1, "minishell: ", 11);
}

void	copy_env(char **envp, t_data *data)
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

void	loop(t_var *var, t_commands *cmd, t_data *data)
{
	int	ret;

	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		var = malloc(sizeof(t_var));
		cmd = malloc(sizeof(t_commands));
		var_initialization(var);
		cmd_initialization(cmd);
		intro();
		ret = get_next_line(0, &var->str);
		if (ret == 666)
		{
			ft_putstr_fd("exit\n", 1);
			exit(g_error);
		}
		parser_str(var);
		analysis_lists(var, cmd, data, &data->envp);
		executor(cmd, data);
		clear_input_list(var);
		clear_struct(cmd);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_var		*var;
	t_commands	*cmd;
	t_data		data;

	argc = 0;
	argv = NULL;
	var = NULL;
	cmd = NULL;
	copy_env(envp, &data);
	loop(var, cmd, &data);
	return (0);
}
