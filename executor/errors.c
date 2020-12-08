#include "../minishell.h"

int error_path(t_commands *command)
{
    ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(command->lst->content, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	return (FAIL);
}

int error_identifier(t_commands *command)
{
	ft_putstr_fd("minishell: unset: `", 1);
	ft_putstr_fd(command->lst->content, 1);
	ft_putstr_fd("\' : not a valid identifier\n", 1);
	return(FAIL);
}

int error_no_file_or_dir(t_commands *command)
{
	ft_putstr_fd("env: ", 1);
	ft_putstr_fd(command->lst->content, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	return(FAIL);
}