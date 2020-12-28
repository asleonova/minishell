#include "../minishell.h"

void get_pipe_2(t_commands *command, t_data *data, int fd[2])
{
     char **argv1;
     pid_t pid;
    
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        add_path_to_commands(command->next, data);
        printf("IN LST: %s\n", command->next->arg_lst->content);
        argv1 = ft_list_to_array(command->next);
        printf("COMMAND_2:%s\n", argv1[0]);
        printf("ARG 1:%s\n", argv1[1]);
        //printf("ARG 2:%s\n", argv1[2]);
       // close(fd[1]); // fd0 больше не нужен
      //  dup2(fd[0], 0); // стандартный ввод - из канала
        //close(fd[0]); // писать в канал не нужно
            // запускаем вторую команду
        if (command->end == 1)
        {
            close(fd[1]); 
            dup2(fd[0], 0);
            pid = fork();
            if (pid == 0)
            {
               
                if(execve(argv1[0], argv1, data->envp) == -1)
                    command_not_found(command);
                free_tab(argv1);
            }
            else 
            {
                wait(&pid);
                g_error = WEXITSTATUS(pid);
            }

        }
}

void pipe_manager(t_commands *command, t_data *data)
{
    int fd[2];
    char **argv;
   
    pid_t pid;
    add_path_to_commands(command, data);
    argv = ft_list_to_array(command);
    printf("COMMAND_1:%s\n", argv[0]);
    if (command->end == 1)
        pipe(fd); // создаем канал для связи
    pid = fork();
    if (pid == -1)
    {
        // обработка ошибки
        strerror(pid);
        exit(errno);
    }
    if (pid == 0) // в дочернем процессе, команда 1
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (command->end == 1)
        {
            close(fd[0]); // читать из канала не нужно
            dup2(fd[1], 1); // стандартный вывод - в канал.
            
            if(execve(argv[0], argv, data->envp) == -1)
                command_not_found(command);
            free_tab(argv);
        }
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        wait(&pid);
        g_error = WEXITSTATUS(pid);
        get_pipe_2(command, data, fd);
    }
}