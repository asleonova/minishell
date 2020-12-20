#include "../minishell.h"

void pipe_manager(t_commands *command, t_data *data)
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
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        dup2(fd[1], 1); // сделали открытый файл стандартным потоком вывода
        close(fd[0]); // закрылили "лишний" дескриптор
        parse_func(command, data); // ????? мб переставить местами, 
        close(fd[1]); // теперь этот дескриптор тоже не нужен.
    }
    else // parent process
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        dup2(fd[0], 0); // fd = fd[0] из пайпа, чтобы в след итерации программы уже читалось из fd пайпа
        close(fd[1]);
        wait(&pid);
        g_error = WEXITSTATUS(pid);
        close(fd[0]);
    }
}