#include "../minishell.h"

int ft_exit_errors(t_commands *command)
{
    int exit_code;
    int i;
    char *arg;

   
    i = 0;
    if (command->count_args == 1) // means we have smth after exit
    {
        arg = ft_strdup(command->lst->content);
        while (arg[i])
        if(!(ft_isalnum(arg[i++])))
            exit_code = 255;
        i++;
    }
    else // if there is more than 1 argument
        exit_code = 1;
    ft_putstr_fd("exit\n", 1);
    if (exit_code == 255)
         ft_putstr_fd("Numeric argument required\n");
    else
        ft_putstr_fd("Too many arguments\n");
    return(exit_code);
}
ft_exit(t_commands *command)
{
    if ()
    exit(0);
}

// custom_error (like that:)
//bash: exit: 344fed: numeric argument required


// void	send_custom_error(char *str)
// {
// 	ft_putstr_fd(SYNTAX_ERROR, 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putchar_fd('\n', 2);
// }