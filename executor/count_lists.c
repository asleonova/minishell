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
		//printf("\nour cmd - %s\n", cmd->cmd);
		// while(cmd->arg_lst != NULL)
		// {
		// 	printf("our argv - %s\n", cmd->arg_lst->content);
		// 	cmd->arg_lst = cmd->arg_lst->next;
		// }
		lst_count++;
		cmd = cmd->next;
	}
	return(lst_count);
}