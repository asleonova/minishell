#include "../minishell.h"

void executor(t_commands *command, char *cmd)
{
    if (command->cmd_list == echo)
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
        sysfuncs(cmd);
}