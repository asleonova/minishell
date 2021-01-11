
#include "../minishell.h"

t_commands *cmd_check(t_commands *cmd, t_data *data)
{
    if(cmd->cmd == NULL && (cmd->fd_1 != -1 || cmd->fd_0 != -1))
	{
		if (cmd->next != NULL)
			clear_struct(cmd);
	}
	if (cmd != NULL && cmd->cmd != NULL && cmd->fd_error != 1)
	{
		cmd_identifier(cmd);
		if ((cmd->count_args > 0 && cmd->command == export) || cmd->command == unset || cmd->command == cd)
		{
			parse_func(cmd, data);
			clear_struct(cmd);
		}
	}
    return(cmd);
}
