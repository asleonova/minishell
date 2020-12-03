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

int main() // testing unset env func
{
	t_data *data;
	char *str;
	data = malloc(sizeof(data));
	str = malloc(sizeof(char) * 4);
	data->envp = (char**)malloc(sizeof(char *) * 4 + 1);
	data->envp[0] = (char*)malloc(sizeof(char *) * 30 + 1);
	data->envp[1] = (char*)malloc(sizeof(char *) * 30 + 1);
	data->envp[2] = (char*)malloc(sizeof(char *) * 30 + 1);
	data->envp[3] = (char*)malloc(sizeof(char *) * 30 + 1);
	
	int j = 0;
	int i = 0;
	char *str1 = "ZSH=/Users/dbliss/.oh-my-zsh"; 
	while (str1[j])
	{
		data->envp[0][i++] = str1[j++];
	}
	i = 0;
	j = 0;
	char *str2 = "USER=dbliss";
	while (str2[j])
	{
		data->envp[1][i++] = str2[j++];
	}
	i = 0;
	j = 0;
	char *str3 = "PWD=/Users/dbliss";
	while (str3[j])
	{
		data->envp[2][i++] = str3[j++];
	}
	i = 0;
	j = 0;
	char *str4 = "OLDPWD=/Users/dbliss";
	while (str4[j])
	{
		data->envp[3][i++] = str4[j++];
	}
	str = "USER";
	printf("%s\n", data->envp[0]);
	printf("%s\n", data->envp[1]);
	printf("%s\n", data->envp[2]);
	printf("%s\n", data->envp[3]);
	delete_env_var(str, data);
	printf("\n\n----UNSET VERSION----\n\n");
	printf("%s\n", data->envp[0]);
	printf("%s\n", data->envp[1]);
	printf("%s\n", data->envp[2]);
	printf("%s\n", data->envp[3]);
	return (0);
}
