#include "../minishell.h"

static void ft_exit_errors(t_commands *command)
{
    int i;
    int flag;
   
    i = -1;
    flag = 0;
    if (command->count_args == 1) // means we have smth after exit
    {
        while (command->arg_lst->content[++i])
            if (ft_isalnum(command->arg_lst->content[++i]) == 0)
        {
            flag = 1;
            g_error = 255;
        }
    }
    else if (command->count_args > 1)// if there is more than 1 argument
    {
        g_error = 1;
        flag = 1;
    }
    ft_putstr_fd("exit\n", 1);
    if (g_error == 255 && flag == 1)
         ft_putstr_fd("Numeric argument required\n", 1);
    else if (g_error == 1 && flag == 1)
        ft_putstr_fd("Too many arguments\n", 1);
}
void ft_exit(t_commands *command)
{
    ft_exit_errors(command);
    exit(g_error);
}