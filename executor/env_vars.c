#include "../minishell.h"

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

void		add_env_var(char *var, t_data *data)
{
	char	**tmp;
	int		i;
	int		len;

	len = tab_len(data->envp); 
	i = 0;
	tmp = (char**)malloc(sizeof(char *) * (len + 2)); // 1 - на новую строку, 1 - для \0
	while (i < len)
	{
		tmp[i] = ft_strdup(data->envp[i]);
		i++;
	}
	tmp[i] = ft_strdup(var);
	tmp[i + 1] = "\0";
	free_tab(data->envp);
	data->envp = tmp;
}

void	delete_env_var(char *var, t_data *data) // deletes the env var and copies the other vars to the new array 
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
		if (ft_strcmp(split[0], var) == 0) // if we have this env var (e.g: PATH, PATH), we don't copy this var to the new array
			free_tab(split);
		else
		{
			free_tab(split);
			tmp[j++] = ft_strdup(data->envp[i]); // otherwise, we just copy the element existed
		} 
	}
	tmp[j] = 0;
	free_tab(data->envp);
	data->envp = tmp;
}

void	change_env_value(char *var, t_data *data)
{
	char *cwd;

	delete_env_var(var, data); // в var будет храниться либо PATH либо OLDPATH
	cwd = getcwd(NULL, 0);
	cwd = ft_strjoin(var, cwd); // не забыть, что тут нужно с PATH= соединить
	add_env_var(cwd, data);
	free(cwd);
}


// void set_env_values(t_data *data)
// {
//     data->home = get_env_values(data->envp, "HOME"); // это нужно куда-то в начало, в иниты
//     // data->cwd = get_env_values(data->envp, "PWD");
//     // data->old_pwd = get_env_values(data->envp, "OLD_PWD");
// }

