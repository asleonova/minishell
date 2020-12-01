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
	tmp = (char**)malloc(sizeof(char *) * (len + 2));
	while (i < len)
	{
		tmp[i] = ft_strdup(data->envp[i]);
		i++;
	}
	tmp[i] = ft_strdup(var);
	tmp[i + 1] = '\0';
	free_tab(data->envp);
	data->envp = tmp;
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
	tmp = (char**)malloc(sizeof(char *) * len); // делаем двумерный массив на кол-во строк
	while (++i < len)
	{
		split = ft_split(data->envp[i], '='); // 1. разделили строку  
		if (ft_strcmp(split[0], var) == 0)
		{
			free_tab(split); 
			continue ;	// тут опять сразу идем в условие while, т.е. код ниже не отрабатывает
		}
		free_tab(split); // 2. очистили строку сплитнутый массив
		tmp[j++] = ft_strdup(data->envp[i]); // 3. записали в tmp строку, которую не удаляем
	}
	tmp[j] = 0;
	free_tab(data->envp); // освободили старый массив
	data->envp = tmp; // записали новый, с удаленным значением
}

void	change_env_value(char *var, t_data *data)
{
	char *cwd;
	char *tmp;

	delete_env_var(var, data); // в var будет храниться либо PATH либо OLDPATH
	cwd = getcwd(NULL, 0);
	cwd = ft_strjoin(var, cwd); // не забыть, что тут нужно с PATH= соединить
	add_env_var(cwd, data);
	free(cwd);
}


void set_env_values(t_data *data)
{
    data->home = get_env_values(data->envp, "HOME"); // это нужно куда-то в начало, в иниты
    data->cwd = get_env_values(data->envp, "PWD");
    data->old_pwd = get_env_values(data->envp, "OLD_PWD");
}

