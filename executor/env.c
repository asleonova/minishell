#include "../minishell.h"

void ft_print_env(t_data *data)
{
    int i;

    i = 0;
    while (data->envp[i])
    {
        if (ft_strchr(data->envp[i], '=') != NULL)
        {
            ft_putstr_fd(data->envp[i], 1);
            ft_putchar_fd('\n', 1);
        }
        i++;
    }    
}
int ft_env(t_data *data, t_commands *command)
{
    int flag;

    flag = 0; // to identify whether we need to print the env or had a mistake
    if (command->count_args == 0)
    {
        ft_print_env(data);
        return(SUCCESS);
    }
    while(command->lst)
    {
        if (ft_strchr(command->lst->content, '=') == NULL)
        {   
            flag = 1;
            error_no_file_or_dir(command);
        }
        else
            ft_export_update(data, command->lst->content);
        command->lst = command->lst->next;
    }
    if (flag == 0)
        ft_print_env(data);
    return (SUCCESS);
}