#include "../minishell.h"

void    check_redirect(t_commands *command) // changes the fd value if there is a redir
{
    command->save_1 = dup(1);
    command->save_0 = dup(0);
    if (command->fd_0 != -1)
    {
        dup2(command->fd_0, 0);
        close(command->fd_0);
    }
    if (command->fd_1 != -1)
    {
        dup2(command->fd_1, 1);
        close(command->fd_1);
    }           
}

char **ft_list_to_array(t_commands *command)
{
    char **argv;
    int i;
    int count;

    i = 1;
    count = ft_lstsize(command->arg_lst);
    argv = (char**)malloc(sizeof(char *) * (count + 2));
    argv[0] = ft_strdup(command->cmd); // copy the command for the 1st element of the array
    while (count > 0)
    {
        argv[i++] = ft_strdup(command->arg_lst->content);
        command->arg_lst = command->arg_lst->next;
        count--;
    }
    argv[i] = 0;
    return(argv);
}

void execute_one_func(t_commands *command, t_data *data)
{
        check_redirect(command);
        cmd_identifier(command);
        if (command->command == bash)
            execute(command, data);
        else
        parse_func(command, data);
}

void executor(t_commands *command, t_data *data) // предполагаю, что хотя бы 1 лист существует (Денис выходит из программы, если в лист ничего не записалось)
{
    int lst_count;

    lst_count = count_list(command);
    command->save_1 = dup(1);
    command->save_0 = dup(0);
    if (lst_count == 1)
            execute_one_func(command, data);  
    else  // значит, был пайп или ; и у нас несколько листов.
        execute(command, data);
    dup2(command->save_0, 0);
    dup2(command->save_1, 1);
    close(command->save_1);
    close(command->save_0);
}