#include "../minishell.h"

char **ft_list_to_array_2(t_commands *command)
{
    char **argv;
    int i;
    int count;

    i = 1;
    count = ft_lstsize(command->next->arg_lst);
    argv = (char**)malloc(sizeof(char *) * count + 2);
    argv[0] = ft_strdup(command->next->cmd); // copy the command for the 1st element of the array
    while (count > 0)
    {
        argv[i++] = ft_strdup(command->arg_lst->content);
        command->next->arg_lst = command->next->arg_lst->next;
        count--;
    }
    argv[i] = 0;
    return(argv);
}

void pipe_manager(t_commands *command, t_data *data)
{
    int fd[2];
    char **argv;
    char **argv1;

    add_path_to_commands(command, data);
    argv = ft_list_to_array(command);
    add_path_to_commands(command->next, data);
    argv1 = ft_list_to_array(command->next);

    pipe(fd); // создаем канал для связи
    if (fork() == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        
        close(fd[0]); // читать из канала не нужно
        dup2(fd[1], 1); // стандартный вывод - в канал.
        close(fd[1]); // fd1 больше не нужен
        // запускаем каоманду
        if(execve(argv[0], argv, data->envp) == -1)
            command_not_found(command);
        free_tab(argv);
    }
    if (fork() == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        close(fd[1]); // fd0 больше не нужен
        dup2(fd[0], 0); // стандартный ввод - из канала
        close(fd[0]); // писать в канал не нужно
            // запускаем вторую команду
        if(execve(argv1[0], argv1, data->envp) == -1)
            command_not_found(command);
        free_tab(argv1);
    }
    // в родительском процессе закрываем оба конца канала
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    g_error = 0;
}
