#include "../minishell.h"

void    check_redirect(t_commands *command) // changes the fd value if there is a redir
{
        if (command->fd_0 != -1)
            dup2(command->fd_0, 0);
        if (command->fd_1 != -1)
            dup2(command->fd_1, 1);
}

char **ft_list_to_array(t_commands *command)
{
    char **argv;
    int i;
    int count;

    i = 1;
    count = ft_lstsize(command->arg_lst);
    argv = (char**)malloc(sizeof(char *) * count + 2);
    argv[0] = ft_strdup(command->cmd); // copy the command for the 1st element of the array
    while (count > 0)
    {
        argv[i++] = ft_strdup(command->arg_lst->content);
        command->arg_lst = command->arg_lst->next;
        count--;
    }
    argv[i] = "\0";
    return(argv);
}

int sysfunc_manager(t_commands *command, t_data *data)
{
    pid_t pid;
    // int status;
    //int fd[2];
    char **argv;

    argv = ft_list_to_array(command); 
    pid = fork();
    if (pid == -1)
    {
        // обработка ошибки
        strerror(pid);
        exit(errno);
    }
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if(execve(command->cmd, argv, data->envp) == -1)
            command_not_found(command);
        // дочерний процесс
    }
    else 
    {
        // родительский процесс
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        wait(&pid);
        g_error = WEXITSTATUS(pid);
    }
    return (1); // the function finally returns a 1, as a signal to the calling function that we should prompt for input again
}

void executor(t_commands *command, t_data *data) // предполагаю, что хотя бы 1 лист существует (Денис выходит из программы, если в лист ничего не записалось)
{
    int lst_count;
    
    lst_count = print_list(command);
    while (command)
    {
        if (lst_count == 1)
            parse_func(command, data);
        else
        {
            pipe_manager(command, data);
            // значит, был пайп и у нас несколько листов.
        }
        command = command->next;
    }
}


