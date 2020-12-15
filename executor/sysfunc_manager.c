#include "../minishell.h"

char **ft_list_to_array(t_commands *command)
{
    char **argv;
    int i;
    int count;

    i = 1;
    count = command->count_args;
    argv = (char**)malloc(sizeof(char *) * command->count_args + 2);
    argv[0] = ft_strdup(command->cmd); // copy the command for the 1st element of the array
    while (count > 0)
    {
        argv[i++] = ft_strdup(command->lst->content);
        command->lst = command->lst->next;
        count--;
    }
    argv[i] = "\0";
    return(argv);
}

int sysfunc_manager(t_commands *command, t_data *data)
{
    pid_t pid;
    int status;
    char **argv;

    argv = ft_list_to_array(command);
    pid = fork();
    if (pid == 0) // child process
    {
        if(execve(command->cmd, argv, data->envp) == -1)
            command_not_found(command);
    }
    else if (pid < 0)
    {
        strerror(pid);
        exit(errno);
    }
    else // parent process
    {
        wait(&pid);
        data->status = WEXITSTATUS(pid);
    }
    return (1); // the function finally returns a 1, as a signal to the calling function that we should prompt for input again
    
}