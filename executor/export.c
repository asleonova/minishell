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
	int diff;

	i = 0;
	while(data->envp[i + 1])
	{
		diff = ft_strcmp(data->envp[i], data->envp[i + 1]);
		if (diff > 0)
			ft_swap(data->envp[i], data->envp[i + 1]);
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

static void		print_vars(t_data *data)
{
	size_t		index;
	char		**splited;
	char		*env;

	index = 0;
	splited = NULL;
	sort_vars(data->env);
	while (data->env[index])
	{
		if (!ft_strmatch(data->env[index], "1=1"))
		{
			env = ft_strchr(data->env[index], '=');
			splited = ft_split(data->env[index], '=');
			if (ft_strncmp(splited[0], "?", 2))
				ft_printf("declare -x %s", splited[0]);
			if (env)
				ft_printf("=\"%s\"\n", env + 1);
			else
				ft_printf("\n");
			ft_clr_darray(splited);
			splited = NULL;
		}
		index++;
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