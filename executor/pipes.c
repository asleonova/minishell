#include "../minishell.h"

// void get_pipe_2(t_commands *command, t_data *data, int fd[2])
// {
//      char **argv1;
//      pid_t pid;

//      argv1 = NULL;
    
//         signal(SIGINT, SIG_DFL);
//         signal(SIGQUIT, SIG_DFL);
//         if (command->end == 1)
//             command = command->next;

//         close(fd[1]); 
//         dup2(fd[0], 0);
//         command->fd_in = fd[0];
//         pid = fork();
//         if (pid == 0)
//         {
//             add_path_to_commands(command, data);
//             argv1 = ft_list_to_array(command);
//             if(execve(argv1[0], argv1, data->envp) == -1)
//                 command_not_found(command);
//             free_tab(argv1);
//         }
//         else 
//         {
//             wait(&pid);
//             g_error = WEXITSTATUS(pid);
//         }   
// }

// void pipe_manager(t_commands *command, t_data *data)
// {
//     int fd[2];
//     char **argv;
//     char **argv1;
//     pid_t pid;
//     pid_t pid_1;


//     argv = NULL;
//     // if (command->end == 1)
//       pipe(fd); // создаем канал для связи
//     pid = fork();
//     if (pid == 0 && command->next != NULL) // в дочернем процессе, команда 1
//     {
//         signal(SIGINT, SIG_DFL);
//         signal(SIGQUIT, SIG_DFL);
//         close(fd[0]); // читать из канала не нужно
//         dup2(fd[1], 1); // стандартный вывод - в канал.
//        // command->save_1 = fd[1];
//         add_path_to_commands(command, data);
//         argv = ft_list_to_array(command);
//            if(execve(argv[0], argv, data->envp) == -1)
//                command_not_found(command);
//            free_tab(argv);
//     }
//     pid_1 = fork();
//     if (pid_1 == 0 && command != NULL)
//     {
//         signal(SIGINT, SIG_DFL);
//         signal(SIGQUIT, SIG_DFL);
//         close(fd[1]); // писать в канал не нужно
//         dup2(fd[0], 0); // стандартный ввод - из канала
//        // command->save_0 = fd[0];
//         command = command->next;
//         add_path_to_commands(command, data);
//         argv1 = ft_list_to_array(command);
//         if(execve(argv1[0], argv1, data->envp) == -1)
//             command_not_found(command);
//         free_tab(argv1);
//     }
//     else
//     {
//         signal(SIGINT, SIG_IGN);
//         signal(SIGQUIT, SIG_IGN);
//         close(fd[0]);
//         close(fd[1]);
//         wait(&pid);
//         wait(&pid_1);
//         g_error = WEXITSTATUS(pid);
//     }
// }

void execute_execve(t_commands *command, t_data *data)
{
    char **argv;
    
    if (ft_strchr(command->cmd, '/') != NULL)
    {
        argv = ft_list_to_array(command);
        if(execve(argv[0], argv, data->envp) == -1)
        {
            command_not_found(command);
            exit(g_error);
        }
            
    }
    else
    {
        add_path_to_commands(command, data);
        argv = ft_list_to_array(command);
        if(execve(argv[0], argv, data->envp) == -1)
        {
            command_not_found(command);
            exit(g_error);
        }

    }
    free(argv);
        
}

void		execute(t_commands *command, t_data *data)
{
	pid_t	pid;
	int		pfd[2];

    
    //check_redirect(command);
    if (command != NULL && command->cmd != NULL)
        pipe(pfd);
	pid = fork();
    if (pid == -1) // in case of error
    {
        strerror(pid);
        exit(errno);
    }
	if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        exec_first_command(command, data, pfd);
    }
	else
	{
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
		wait(&pid);
		g_error = WEXITSTATUS(pid);
		check_pipe(data, command, pfd);
	}
}

int		exec_first_command(t_commands *command, t_data *data, int pfd[2])
{
    // char **argv;
    // argv = NULL;

	if (command != NULL && command->cmd != NULL)
	{
		if (command->end == 1)
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
		}
        // add_path_to_commands(command, data);
        // argv = ft_list_to_array(command);
        // if(execve(argv[0], argv, data->envp) == -1)
        //     command_not_found(command);
        // free_tab(argv);
        check_redirect(command);
        cmd_identifier(command);
        if (command->command == bash)
            execute_execve(command, data);
        else
            parse_func(command, data);
    }
	return (0);
}

int		check_pipe(t_data *data, t_commands *command, int pfd[2])
{
	if (command->next != NULL && command->next->cmd != NULL)
	{
        if (command->end != 2)
        {
            close(pfd[1]);
	        dup2(pfd[0], 0);
		    execute(command->next, data);
        }
        else
            execute_one_func(command->next, data);
       //dup2(command->save_0, 0);
	}
	return (0);
}