#include "../minishell.h"

char **get_paths(t_data *data, t_commands *command)
{
    char *path;
    char **paths;

    if (!path_exist(data, "PATH"))
    {
        path_no_file_or_dir(command);
        paths = NULL;
    }
    else
    {
        path = get_env_values(data, "PATH");
        paths = ft_split(path, ':');
        free(path);
    }
    return (paths);    
}

void add_path_to_commands(t_commands *command, t_data *data)
{
    char **paths;
    char *join;
    char *cmd;
    int i;
    struct stat buf;

    i = 0;
    cmd = NULL;
    paths = get_paths(data, command);
    while(paths[i])
    {
        join = ft_strjoin(paths[i], "/");
        cmd = ft_strjoin(join, command->cmd);
        free(join);
        if (stat(cmd, &buf) == 0)
            break;
        i++;
    }
    free_tab(paths);
    command->cmd = cmd;
    free(cmd);
}

void command_for_exec(t_commands *command, t_data *data)
{
    if (ft_strchr(command->cmd, '/') != NULL)
        sysfunc_manager(command, data);
    else
    {
        add_path_to_commands(command, data);
        sysfunc_manager(command, data);
    }
        
}

int sysfunc_manager(t_commands *command, t_data *data)
{
    pid_t pid;
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
        if(execve(argv[0], argv, data->envp) == -1)
            command_not_found(command);
        free(argv);
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