#include "../minishell.h"

void error_path(t_commands *command)
{
    ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(command->lst, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
}
