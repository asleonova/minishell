#include "../minishell.h"

static void	ft_swap(char *s1, char *s2)
{
	char *tmp;

	*tmp = *s1;
	*s1 = *s2;
	*s2 = *tmp;
}

static void	ft_sort_list(t_data *data)
{
	int i;
	int j;
	int len;
	int diff;

	i = 0;
	len = tab_len(data->envp);
	while(i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			diff = ft_strcmp(data->envp[j], data->envp[j + 1]);
			if (diff > 0)
				ft_swap(&data->envp[j], &data->envp[j + 1]);
			j++;
		}
		i++;
	}
}

static void ft_print_export(t_data *data)
{
    int i;
    char **split;
	char *var;

    i = 0;
    ft_sort_list(data);
    while (data->envp[i])
    {
		var = ft_strchr(data->envp[i], '=');
        split = ft_split(data->envp[i], '=');
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(split[0], 1);
        if (var)
        {
			ft_putchar_fd('=', 1);
            ft_putchar_fd('"', 1);
			if (split[1])
            	ft_putstr_fd(split[1], 1);
            ft_putchar_fd('"', 1);
		}
        ft_putchar_fd('\n', 1);
        free_tab(split);
        i++;
    }
}

static void		ft_unset_env(char *str, t_data *data)
{
	char	*tmp;

		if ((tmp = get_env_values(str, data)) != NULL)
		{
			free(tmp);
			delete_env_var(str, data);
		}
}

void ft_export_update(t_data *data, char *str)
{
	char	**temp;

	temp = ft_split(str, '=');
	ft_unset_env(temp[0], data);
	free_tab(temp);
	add_env_var(str, data);
}

int			ft_export(t_data *data, t_commands *command)
{
	if (command->count_args == 0)
	{
		ft_print_export(data);
		return(SUCCESS);
	}
	while (command->lst)
	{
		ft_export_update(data, command->lst->content);
		command->lst = command->lst->next;
	}
	ft_print_export(data); // вот это чекнуть. вроде печатать не нужно!!!
	return(SUCCESS);
}

// int main() // testing unset env func
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
// 	command->lst = ft_lstnew("dZSHC=dffsd");
// 	append_lst(&command->lst, "heeeey");
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
// 	printf("\n\n----PRINT EXPORT----\n\n");
// 	ft_export(data, command);
// 	return (0);
// }