#include "../minishell.h"

int ft_echo(t_commands *command)
{
    int flag;
    flag = 0;

    if (command->count_args == 0)
    {
        write(1, "\n", 1);
        return(SUCCESS);
    }
    while(command->arg_lst)
    {
        if (ft_strcmp("-n", command->arg_lst->content) == 0)
        {
            if(command->arg_lst->next != NULL)
                command->arg_lst = command->arg_lst->next;
            flag = 1;
        }
        if (ft_strcmp("-n", command->arg_lst->content) != 0)
            ft_putstr_fd(command->arg_lst->content, 1);
        if (command->arg_lst->next != NULL)
            write(1, " ", 1);
        command->arg_lst = command->arg_lst->next;
    }
    if (flag == 0)
        write(1, "\n", 1);
    return(SUCCESS); 
}