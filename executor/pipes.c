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
    pid_t pid1;
    pid_t pid2;
   // pid = fork();
    // if (pid == -1)
    // {
    //     // обработка ошибки
    //     strerror(pid);
    //     exit(errno);
    // }

    pipe(fd); // создаем канал для связи
    pid1 = fork();
    {
       // if (command->next != NULL)
        //{
            //signal(SIGINT, SIG_DFL);
        //signal(SIGQUIT, SIG_DFL);

        add_path_to_commands(command, data);
        argv = ft_list_to_array(command);
            //         printf("LIST ARG: %s\n", command->cmd);
            // printf("ARGV: %s\n", argv[0]);
        close(fd[0]); // читать из канала не нужно
        dup2(fd[1], 1); // стандартный вывод - в канал.
        close(fd[1]); // fd1 больше не нужен
        // запускаем каоманду
        if(execve(argv[0], argv, data->envp) == -1)
            command_not_found(command);
        }
        pid2 = fork();
    if (pid2 == 0)
        {
            add_path_to_commands(command->next, data);
            argv1 = ft_list_to_array(command->next);
            // printf("LIST ARG: %s\n", command->next->cmd);
            // printf("ARGV: %s\n", argv1[0]);
            close(fd[1]); // fd0 больше не нужен
            dup2(fd[0], 0); // стандартный ввод - из канала
            close(fd[0]); // писать в канал не нужно
            // запускаем вторую команду
  
            execve(argv1[0], argv1, data->envp);
                // command_not_found(command->next);
        }
    // в родительском процессе закрываем оба конца канала
        {
            close(fd[0]);
        close(fd[1]);
        wait(&pid1);
        wait(&pid2);
      //  wait(NULL);
        g_error = 0;
        }
}


    // else 
    // {
    //     close (command->fd[0]);
    //     close (command->fd[1]);
    //     wait(&pid);
    //     g_error = WEXITSTATUS(pid);
    // }
    // pid = fork();
    // if (pid == 0) // other child process
    // {
    //     signal(SIGINT, SIG_IGN);
    //     signal(SIGQUIT, SIG_IGN);
    //     close(command->fd[1]);
    //     dup2(command->fd[0], 0); // fd = fd[0] из пайпа, чтобы в след итерации программы уже читалось из fd пайпа
    //     close(command->fd[0]);
    //     parse_func(command, data);
    // }
    // // else
    // // {
    // //     close (command->fd[0]);
    // //     close (command->fd[1]);
    // //     wait(&pid);
    // //     g_error = WEXITSTATUS(pid);
    // // }
// }

