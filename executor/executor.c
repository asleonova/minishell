#include "../minishell.h"

int		check_redirect(t_commands *command) // returns -1 if there was no redirect
{
    if (command->type_redir != -1)
    {
        if (command->type_redir == back_redir) // <
            dup2(command->fd_0, 0);
        else // > or >>
            dup2(command->fd_1, 1);
    }
	return (command->type_redir);
}

int parse_func(t_commands *command, t_data *data)
{   
    check_redirect(command);
    if (command->invalid == 1)
        return(FAIL); // не забыть текст ошибки
    else if (command->cmd_list == echo)
        ft_echo(command);
    else if (command->cmd_list == cd)
        ft_cd(command);
    else if (command->cmd_list == pwd)
        ft_pwd(command);
    else if (command->cmd_list == export)
        ft_export(command);
    else if (command->cmd_list == unset)
        ft_unset(command);
    else if (command->cmd_list == our_exit)
        ft_exit(command);
    else if (command->cmd_list == env)
        ft_env(command);
    else
        sysfunc_manager(command, data);
    return (SUCCESS);
}

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
        if(execve(command->cmd, argv, data->envp) == -1)
            command_not_found(command);
        // дочерный процесс
    }
    else 
    {
        // родительский процесс
        wait(&pid);
        data->status = WEXITSTATUS(pid);
    }
    return (1); // the function finally returns a 1, as a signal to the calling function that we should prompt for input again
}

void executor(t_commands *command, t_list *lst, t_data *data) // предполагаю, что хотя бы 1 лист существует (Денис выходит из программы, если в лист ничего не записалось)
{
    int lst_count;
    
    lst_count = ft_lstsize(lst);
    while (lst)
    {
        if (lst_count == 1)
            parse_func(command, data);
        else
        {
            pipe_manager(command, data);
            // значит, был пайп и у нас несколько листов.
        }
        lst = lst->next;
    }
}

int pipe_manager(t_commands *command, t_data *data)
{
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();
    if (pid == -1)
    {
        // обработка ошибки
        strerror(pid);
        exit(errno);
    }
    if (pid == 0)
    {
        // command->fd_0 = fd[0];
        // command->fd_1 = fd[1];
        dup2(fd[1], 1); // сделали открытый файл стандартным потоком вывода
        close(fd[0]); // закрылили "лишний" дескриптор
        parse_func(command, data); // ????? мб переставить местами, 
        close(fd[1]); // теперь этот дескриптор тоже не нужен.
    }
    else // parent process
    {
        dup2(fd[0], 0); // fd = fd[0] из пайпа, чтобы в след итерации программы уже читалось из fd пайпа
        close(fd[1]);
        wait(&pid);
        data->status = WEXITSTATUS(pid);
        close(fd[0]);
    }
}



