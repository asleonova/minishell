#include "../minishell.h"

void    cmd_identifier(t_commands *command)
{
    command->count_args = ft_lstsize(command->arg_lst);
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

void parse_func(t_commands *command, t_data *data)
{
    int ret;

    ret = 0;
    
    command->count_args = ft_lstsize(command->arg_lst);
    check_redirect(command); 
    if (command->command == echo)
        ret = ft_echo(command);
    else if (command->command == cd)
        ret = ft_cd(command, data);
    else if (command->command == pwd)
        ret = ft_pwd();
    else if (command->command == export)
        ret = ft_export(data, command);
    else if (command->command == unset)
        ret = ft_unset(data, command);
    else if (command->command == our_exit)
        ft_exit(command);
    else
        ret = ft_env(command, data);
    g_error = ret;
}