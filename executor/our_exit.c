#include "../minishell.h"

static void ft_exit_errors(t_commands *command)
{
    int i;
    char *arg;

   
    i = 0;
    if (command->count_args > 0) // means we have smth after exit
    {
        arg = ft_strdup(command->arg_lst->content);
        while (arg[i])
        if(!(ft_isalnum(arg[i++])))
            g_error = 255;
        i++;
    }
    else // if there is more than 1 argument
        g_error = 1;
    ft_putstr_fd("exit\n", 1);
    if (g_error == 255)
         ft_putstr_fd("Numeric argument required\n", 1);
    else
        ft_putstr_fd("Too many arguments\n", 1);
}
void ft_exit(t_commands *command)
{
    ft_exit_errors(command);
    exit(g_error);
}

// custom_error (like that:)
//bash: exit: 344fed: numeric argument required


// void	send_custom_error(char *str)
// {
// 	ft_putstr_fd(SYNTAX_ERROR, 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putchar_fd('\n', 2);
// }