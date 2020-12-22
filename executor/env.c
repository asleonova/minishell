#include "../minishell.h"

static int path_exist(t_data *data, char *key) // need to check if the $PATH exists
{
    int i;
    char **tmp;
	int found;

    i = -1;
	found = 0;
    while (data->envp[++i])
	{
		tmp = ft_split(data->envp[i], '=');
		if (ft_strcmp(tmp[0], key) == 0) // PATH == PATH
		{
			found = 1;
			break;
		}
		free_tab(tmp);
	}
	return(found);
}

static int ft_print_env(t_data *data, t_commands *command) // переписать без аргументов!
{
    int i;

    i = 0;
	if (!path_exist(data, "PATH"))
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 1);
		return (FAIL);
	}
    while (data->envp[i])
    {
        if (ft_strchr(data->envp[i], '=') != NULL)
        {
            ft_putstr_fd(data->envp[i], 1);
            ft_putchar_fd('\n', 1);
        }
		else 
			error_no_file_or_dir(command);	
        i++;
    }
	return(SUCCESS);   
}
int ft_env(t_data *data, t_commands *command)
{
    int flag;

    flag = 0; // to identify whether we need to print the env or had a mistake
    if (command->count_args == 0)
    {
        ft_print_env(data, command);
        return(SUCCESS);
    }
    while(command->arg_lst)
    {
        if (ft_strchr(command->arg_lst->content, '=') == NULL)
        {   
            flag = 1;
            error_no_file_or_dir(command);
        }
        else
            ft_export_update(data, command->arg_lst->content);
        command->arg_lst = command->arg_lst->next;
    }
    if (flag == 0)
        ft_print_env(data, command);
    return (SUCCESS);
}
// int main() // testing env env func
// {
// 	t_data *data;
// 	t_commands *command;
	
// 	data = malloc(sizeof(t_data));
// 	command = malloc(sizeof(t_commands));
// 	command->count_args = 1;
// 	data->envp = (char**)malloc(sizeof(char *) * 4 + 1);
// 	data->envp[0] = ft_strdup("ZSHC=/Users/dbliss/.oh-my-zsh");
// 	data->envp[1] = ft_strdup("CSERR=dbliss");
// 	data->envp[2] = ft_strdup("anna=");
// 	data->envp[3] = ft_strdup("sfkjsfklfsjl=flsfl");
// 	data->envp[4] = NULL;
// 	command->lst = ft_lstnew("anna=");
// 	append_lst(&command->lst, "ZSHC");
// 	append_lst(&command->lst, "heeeey=");
// 	printf("\n\n----PRINT LST----\n\n");
// 	printf("%s\n", command->lst->content);
// 	printf("%s\n", command->lst->next->content);
// 	printf("%s\n", command->lst->next->next->content);
// 	printf("\n\n----LST END----\n\n");
// 	printf("%s\n", data->envp[0]);
// 	printf("%s\n", data->envp[1]);
// 	printf("%s\n", data->envp[2]);
// 	printf("%s\n", data->envp[3]);
// 	printf("\n\n----PRINT ENV----\n\n");
// 	ft_env(command, data);
// 	printf("\n\n----AFTER ENV----\n\n");
// 	printf("%s\n", data->envp[0]);
// 	printf("%s\n", data->envp[1]);
// 	printf("%s\n", data->envp[2]);
// 	printf("%s\n", data->envp[3]);
// 	return (0);
// }