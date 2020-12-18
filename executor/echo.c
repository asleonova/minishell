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
    while(command->lst)
    {
        if (ft_strcmp("-n", command->lst->content) == 0)
        {
            if(command->lst->next != NULL)
                command->lst = command->lst->next;
            flag = 1;
        }
        if (ft_strcmp("-n", command->lst->content) != 0)
            ft_putstr_fd(command->lst->content, 1);
        if (command->lst->next != NULL)
            write(1, " ", 1);
        command->lst = command->lst->next;
    }
    if (flag == 0)
        write(1, "\n", 1);
    return(SUCCESS); 
}

// void echo_check()
// {
//     t_commands command;
//     command.lst = NULL;
//     command.lst = (t_list *) malloc(sizeof(t_list));
//     command.lst->content = "hello";
//     // command.lst->next = NULL;
//     command.lst->next = (t_list *) malloc(sizeof(t_list));
//     command.lst->next->content = "hello";
//     command.lst->next->next = (t_list *) malloc(sizeof(t_list));
//     command.lst->next->next->content = "world"; 
//     command.lst->next->next->next = NULL;
//     command.cmd = "echo";
//     command.count_args = 1;
//     ft_echo(&command);
// }

// int main()
// {
//     echo_check();
//     return (0);
// }