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

int main() // testing env env func
{
	t_data *data;
	t_commands *command;
	
	data = malloc(sizeof(t_data));
	command = malloc(sizeof(t_commands));
	command->count_args = 1;
	data->envp = (char**)malloc(sizeof(char *) * 4 + 1);
	data->envp[0] = ft_strdup("ZSHC=/Users/dbliss/.oh-my-zsh");
	data->envp[1] = ft_strdup("CSERR=dbliss");
	data->envp[2] = ft_strdup("anna=");
	data->envp[3] = ft_strdup("sfkjsfklfsjl=flsfl");
	data->envp[4] = NULL;
	command->lst = ft_lstnew("anna=");
	append_lst(&command->lst, "ZSHC");
	append_lst(&command->lst, "heeeey=");
	printf("\n\n----PRINT LST----\n\n");
	printf("%s\n", command->lst->content);
	printf("%s\n", command->lst->next->content);
	printf("%s\n", command->lst->next->next->content);
	printf("\n\n----LST END----\n\n");
	printf("%s\n", data->envp[0]);
	printf("%s\n", data->envp[1]);
	printf("%s\n", data->envp[2]);
	printf("%s\n", data->envp[3]);
	printf("\n\n----PRINT ENV----\n\n");
	ft_env(data, command);
	printf("\n\n----AFTER ENV----\n\n");
	printf("%s\n", data->envp[0]);
	printf("%s\n", data->envp[1]);
	printf("%s\n", data->envp[2]);
	printf("%s\n", data->envp[3]);
	return (0);
}