#include "../minishell.h"

int ft_export(t_data *data, char *arg)
{
	char	**temp;

	temp = ft_split(arg, '=');
	delete_env_var(temp[0], data);
	free_args(temp);
	add_env_var(arg, data);
}