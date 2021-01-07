#include "../minishell.h"

char **get_paths(t_data *data)
{
    char *path;
    char **paths;

    path = get_env_values(data, "PATH");
    paths = ft_split(path, ':');
    free(path);
    return (paths);
}

void add_path_to_commands(t_commands *command, t_data *data)
{
    char **paths;
    char *join;
    char *cmd;
    int i;
    struct stat buf;

    i = 0;
    cmd = NULL;
    paths = get_paths(data);
    while(paths[i])
    {
        join = ft_strjoin(paths[i], "/");
        cmd = ft_strjoin(join, command->cmd);
        free(join);
        if (stat(cmd, &buf) == 0)
            break;
        i++;
    }
    free_tab(paths);
    command->cmd = cmd;
    free(cmd);
}

int path_exist(t_commands *command, t_data *data) // need to check if the $PATH exists
{
    int i;
    char **tmp;
	int found;

    i = -1;
	found = 0;
    while (data->envp[++i])
	{
		tmp = ft_split(data->envp[i], '=');
		if (ft_strcmp(tmp[0], "PATH") == 0) // PATH == PATH
		{
			found = 1;
			break;
		}
		free_tab(tmp);
	}
	if (data->envp[i] == NULL)
		path_no_file_or_dir(command);
	return(found);
}

void path_does_not_exist(t_commands *command, t_data *data)
{
	if(!path_exist(command, data))
		exit(g_error);
}