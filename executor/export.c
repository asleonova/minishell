#include "../minishell.h"

void	ft_swap(char *s1, char *s2)
{
	char *tmp;

	*tmp = *s1;
	*s1 = *s2;
	*s2 = *tmp;
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

int ft_export_update(t_data *data, char *arg) // это поменять значение уже существующей переменной
{
	char	**temp;

	temp = ft_split(arg, '=');
	delete_env_var(temp[0], data);
	free_args(temp);
	add_env_var(arg, data);
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

void	ft_export(t_data *data, t_commands *command)
{
	int i;

	i = 0;
	if (command->count_args == 0)
		ft_print_export(data);
	else
	{
		while (data->envp[i])
		{
			ft_export_update(data, data->envp[i]);
			i++;
		}
		ft_print_export(data);
	}
}