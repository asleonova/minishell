#include "../minishell.h"

int ft_unset(t_data *data, t_commands *command)
{
	while (command->arg_lst)
	{
		if (ft_strchr(command->arg_lst->content, '=') == NULL)
			ft_unset_env(command->arg_lst->content, data);
		else
			error_identifier(command);
		command->arg_lst = command->arg_lst->next;
	}
	return(SUCCESS);
}	