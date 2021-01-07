#include "../minishell.h"

int ft_env(t_commands *command, t_data *data) // переписать без аргументов!
{
    int i;

    i = 0;
	if (!path_exist(command, data))
		return(g_error);
    while (data->envp[i])
    {
        if (ft_strchr(data->envp[i], '=') != NULL)
        {
            ft_putstr_fd(data->envp[i], 1);
            ft_putchar_fd('\n', 1);
        }
        i++;
    }
	return(SUCCESS);   
}