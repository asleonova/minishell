#include "../minishell.h"

int ft_unset(t_data *data, t_commands *command)
{
    if (command->count_args > 0)
    {
        while (command->lst)
        {
            if (ft_strchr(command->lst->content, '=') == NULL)
                ft_unset_env(command->lst->content, data);
            else
                error_identifier(command);
        command->lst = command->lst->next;
        }

    }
    return(SUCCESS);
}