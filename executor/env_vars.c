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

void		update_pwd(t_main *main, int type)
{
	char		*pwd;
	char		*tmp;
	char		*env;

	if (!(pwd = getcwd(NULL, 0)))
		return ;
	if (!(env = get_env_value(main, (type == 0) ? "PWD" : "OLDPWD")))
	{
		free(pwd);
		return ;
	}
	unset_env(main, (type == 0) ? "PWD" : "OLDPWD");
	tmp = pwd;
	pwd = ft_strjoin((type == 0) ? "PWD=" : "OLDPWD=", pwd);
	export_env(main, pwd);
	free(env);
	free(tmp);
	free(pwd);
}

int			change_directory(t_command *command, t_main *main)
{
	int		status;

	ft_get_pipe(main, command->pipe, 0);
	check_redirect(command);
	if (command->pipe == NULL)
	{
		if (command->args[1] == NULL || command->args[1][0] == '~')
			status = get_home_path(command->args[1], main);
		else
		{
			update_pwd(main, 1);
			status = chdir(command->args[1]);
			if (status == 0)
				update_pwd(main, 0);
		}
		if (status == -1)
			send_custom_error("Not a valid path");
	}
	ft_get_pipe(main, command->pipe, 1);
	return (1);
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

