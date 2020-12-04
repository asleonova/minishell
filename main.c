#include <unistd.h>
#include "minishell.h"
#include <stdio.h>

void		free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		tab_len(char **tab)
{
	int	len;
	
	len = 0;
	while (tab[len])
		len++;
	return(len);

}

void	delete_env_var(char *var, t_data *data)
{
	char **tmp;
	char **split;
	int i;
	int len;
	int j;
	
	len = tab_len(data->envp);
	i = -1;
	j = 0;
	tmp = (char**)malloc(sizeof(char *) * len);
	while (++i < len)
	{
		split = ft_split(data->envp[i], '=');
		if (ft_strcmp(split[0], var) == 0)
			free_tab(split);
		else
		{
			free_tab(split);
			tmp[j++] = ft_strdup(data->envp[i]);
		} 
	}
	tmp[j] = 0;
	free_tab(data->envp);
	data->envp = tmp;
}

void		add_env_var(char *var, t_data *data)
{
	char	**tmp;
	int		i;
	int		len;

	len = tab_len(data->envp); 
	i = 0;
	tmp = (char**)malloc(sizeof(char *) * (len + 2));
	while (i < len)
	{
		tmp[i] = ft_strdup(data->envp[i]);
		i++;
	}
	tmp[i] = ft_strdup(var);
	tmp[i + 1] = NULL;
	free_tab(data->envp);
	data->envp = tmp;
}

char *get_env_values(t_data *data, char *key)
{
    int i;
    char **tmp;
    char *value;

    i = -1;
    value = NULL;
    while (data->envp[++i])
	{
		tmp = ft_split(data->envp[i], '=');
		if (ft_strcmp(tmp[0], key) == 0)
		{
			if (tmp[1] == NULL)
				value = ft_strdup(" ");
			else
				value = ft_strdup(tmp[1]);
			break ;
		}
		free_tab(tmp);
	}
	return (value);
}

void	ft_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	ft_sort_list(t_data *data)
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

void ft_print_export(t_data *data)
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

void		ft_unset_env(t_data *main, char *arg)
{
	char	*temp;

	// if (ft_strchr(arg, '=') == NULL)
	// {
		if ((temp = get_env_values(main, arg)) != NULL)
		{
			free(temp);
			delete_env_var(arg, main);
		}
	// }
	else
		printf("Error argument!");
}

void ft_export_update(t_data *data, char *arg) // это поменять значение уже существующей переменной
{
	char	**temp;

	temp = ft_split(arg, '=');
	ft_unset_env(data,temp[0]);
	free_tab(temp);
	add_env_var(arg, data);
}

void	ft_export(t_data *data, t_commands *command)
{
	int i;
	char **tmp;
	int len;

	len = tab_len(data->envp);
	i = 0;
	if (command->count_args == 0)
		ft_print_export(data);
	else
	{
		while (data->envp[i])
		{
			tmp = ft_split(data->envp[i], "=");
			if (ft_strcmp(tmp[0], data->envp[len]) == 0) // если последний элемент - такой же есть
				// delete one and update!!!! НЕ ПОЛУЧТЬСЯ!!!! ТАК КАК МОЖНО МНОГО ПЕРЕМЕННЫХ ДОБАВЛЯТЬ!!!!
			ft_strcmp(data, data->envp[i]);
			i++;
		}
		ft_print_export(data);
	}
}
int main() // testing unset env func
{
	t_data *data;
	t_commands *command;

	char *str;
	data = malloc(sizeof(data));
	command = malloc(sizeof(command));
	str = malloc(sizeof(char) * 4);
	data->envp = (char**)malloc(sizeof(char *) * 4 + 1);
	data->envp[0] = (char*)malloc(sizeof(char *) * 30 + 1);
	data->envp[1] = (char*)malloc(sizeof(char *) * 30 + 1);
	data->envp[2] = (char*)malloc(sizeof(char *) * 30 + 1);
	data->envp[3] = (char*)malloc(sizeof(char *) * 30 + 1);
	data->envp[4] = NULL;
	
	int j = 0;
	int i = 0;
	command->count_args = 4;
	char *str1 = "ZSHC=/Users/dbliss/.oh-my-zsh"; 
	while (str1[j])
	{
		data->envp[0][i++] = str1[j++];
	}
	i = 0;
	j = 0;
	char *str2 = "CSERR=dbliss";
	while (str2[j])
	{
		data->envp[1][i++] = str2[j++];
	}
	i = 0;
	j = 0;
	char *str3 = "abt=";
	while (str3[j])
	{
		data->envp[2][i++] = str3[j++];
	}
	i = 0;
	j = 0;
	char *str4 = "abc=";
	while (str4[j])
	{
		data->envp[3][i++] = str4[j++];
	}
	str = "USER";
	printf("%s\n", data->envp[0]);
	printf("%s\n", data->envp[1]);
	printf("%s\n", data->envp[2]);
	printf("%s\n", data->envp[3]);
	// delete_env_var(str, data);
	// printf("\n\n----UNSET VERSION----\n\n");
	printf("\n\n----PRINT EXPORT----\n\n");
	ft_export(data, command);
	// printf("%s\n", data->envp[0]);
	// printf("%s\n", data->envp[1]);
	// printf("%s\n", data->envp[2]);
	// printf("%s\n", data->envp[3]);
	return (0);
}
