#include "../minishell.h"

void    check_redirect(t_commands *command) // changes the fd value if there is a redir
{
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

void executor(t_commands *command, t_data *data) // предполагаю, что хотя бы 1 лист существует (Денис выходит из программы, если в лист ничего не записалось)
{
    int lst_count;

    lst_count = count_list(command);
    //printf("LST COUNT: %d\n", lst_count);
    check_redirect(command);
    command->save_1 = dup(1);
    command->save_0 = dup(0);
    if (lst_count == 1)
    {
        parse_func(command, data);
        // dup2(command->save_1, 1);
        // dup2(command->save_0, 0);
        // close(command->save_1);
        // close(command->save_0);
        }
    else  // значит, был пайп и у нас несколько листов.
    {
        execute_another_function(data, command);
        // while (command)
        // {
        //     pipe_manager(command, data);
        //    // printf("CMD: %s\n", command->cmd);
        //     //dup2(command->save_0, 0);
        //    // dup2(command->save_1, 1);
        //     printf("CMD: %s\n", command->cmd);
        //     command = command->next;
      
        // }
        dup2(command->save_0, 0);
		dup2(command->save_1, 1);

    }

    // close(command->save_1);
    // close(command->save_0);
}