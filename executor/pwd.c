#include "../minishell.h"

int ft_pwd(t_commands *command)
{
    char *cwd;
    
    cwd = getcwd(NULL, 1000);
    ft_putstr_fd(cwd, 1);
    write(1, "\n", 1);
    free(cwd);
    return (SUCCESS);
}