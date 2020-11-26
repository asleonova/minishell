#include "../minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

int ft_echo(t_commands *command)
{
    if (command->count_args == 0)
    {
        write(1, "\n", 1);
        return(SUCCESS);
    }
    while(command->lst) // надо чекнуть как по листам правильно двигаться
    {
        if (ft_strcmp("-n", command->lst->content) == 0)
            command->lst = command->lst->next;
        ft_putstr_fd(command->lst->content, 1);
        if (command->lst->next != NULL)
            write(1, " ", 1);
        command->lst = command->lst->next;
    }
    if (ft_strcmp("-n", command->lst->content) != 0)
        write(1, "\n", 1);
    return(SUCCESS); 
}

int main()
{
    t_commands command;
    command.lst = NULL;
    command.lst = (t_list *) malloc(sizeof(t_list));
    command.lst->content = "hello";
    command.lst->next = NULL;
    //command.lst->content = "-n";
    //command.lst->next = (t_list *) malloc(sizeof(t_list));
    //command.lst->content = "hello";
    //command.lst->next->next = NULL;
    //command.cmd = "echo";
    command.count_args = 1;
    ft_echo(&command);
    return (0);
}