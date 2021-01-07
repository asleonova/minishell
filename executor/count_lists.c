#include "../minishell.h"

int count_list(t_commands *cmd)
{
	int lst_count;
	lst_count = 0;
	while(cmd->prev != NULL)
	{
		cmd = cmd->prev;
	}
	while(cmd != NULL)
	{
		lst_count++;
		cmd = cmd->next;
	}
	return(lst_count);
}