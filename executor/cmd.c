#include "../minishell.h"

static void    cmd_identifier(t_commands *command)
{
    if (ft_strcmp(command->cmd, "echo") == 0)
        command->command = echo;
    else if (ft_strcmp(command->cmd, "cd") == 0)
         command->command = cd;
    else if (ft_strcmp(command->cmd, "pwd") == 0)
        command->command = pwd;
    else if (ft_strcmp(command->cmd, "export") == 0)
        command->command = export;
    else if (ft_strcmp(command->cmd, "unset") == 0)
        command->command = unset;
    else if (ft_strcmp(command->cmd, "exit") == 0)
        command->command = our_exit;
    else if (ft_strcmp(command->cmd, "env") == 0)
        command->command = env;
    else 
        command->command = bash;
}

int parse_func(t_commands *command, t_data *data)
{
    cmd_identifier(command);   
    command->count_args = ft_lstsize(command->arg_lst);
    if (command->invalid == 1)
        return(FAIL); // не забыть текст ошибки
    else if (command->command == echo)
        ft_echo(command);
    else if (command->command == cd)
        ft_cd(command, data);
    else if (command->command == pwd)
        ft_pwd();
    else if (command->command == export)
        ft_export(data, command);
    else if (command->command == unset)
        ft_unset(data, command);
    else if (command->command == our_exit)
        ft_exit(command);
    else if (command->command == env)
        ft_env(data, command);
    else
        command_for_exec(command, data);
    return (SUCCESS);
}