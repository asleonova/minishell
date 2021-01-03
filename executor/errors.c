#include "../minishell.h"

int error_path(t_commands *command)
{
    ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(command->arg_lst->content, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	g_error = 1;
	return (g_error);
}

int error_identifier(t_commands *command)
{
	ft_putstr_fd("minishell: unset: `", 1);
	ft_putstr_fd(command->arg_lst->content, 1);
	ft_putstr_fd("\' : not a valid identifier\n", 1);
	g_error = 1;
	return(g_error);
}

int error_no_file_or_dir(t_commands *command)
{
	ft_putstr_fd("env: ", 1);
	ft_putstr_fd(command->arg_lst->content, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	g_error = 127;
	return(g_error);
}

int command_not_found(t_commands *command)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(command->cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	g_error = 127;
	return(g_error);
}

void	permission_denied(t_commands *command)
{
	if (errno != 0)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(strerror(errno), 1);
		ft_putchar_fd('\n', 1);
		command->cmd = NULL;
		g_error = 1;
		close(command->fd_0);
    	close(command->fd_1);
	}
}
