#include "../minishell.h"

void ft_unset(t_data *data, t_commands *command)
{
	while (command->lst)
	{
		if (ft_strchr(command->lst->content, '=') == NULL)
			ft_unset_env(command->lst->content, data);
		else
			error_identifier(command);
		command->lst = command->lst->next;
	}
}

int main() // testing unset env func
{
	t_data *data;
	t_commands *command;
	
	data = malloc(sizeof(t_data));
	command = malloc(sizeof(t_commands));
	command->count_args = 1;
	data->envp = (char**)malloc(sizeof(char *) * 4 + 1);
	data->envp[0] = ft_strdup("ZSHC=/Users/dbliss/.oh-my-zsh");
	data->envp[1] = ft_strdup("CSERR=dbliss");
	data->envp[2] = ft_strdup("anna=");
	data->envp[3] = ft_strdup("sfkjsfklfsjl=flsfl");
	data->envp[4] = NULL;
	command->lst = ft_lstnew("anna");
	append_lst(&command->lst, "ZSHC");
	append_lst(&command->lst, "heeeey=");
	printf("\n\n----PRINT LST----\n\n");
	printf("%s\n", command->lst->content);
	printf("%s\n", command->lst->next->content);
	printf("%s\n", command->lst->next->next->content);
	printf("\n\n----LST END----\n\n");
	printf("%s\n", data->envp[0]);
	printf("%s\n", data->envp[1]);
	printf("%s\n", data->envp[2]);
	printf("%s\n", data->envp[3]);
	printf("\n\n----PRINT UNSET----\n\n");
	ft_unset(data, command);
	printf("\n\n----AFTER UNSET----\n\n");
	printf("%s\n", data->envp[0]);
	printf("%s\n", data->envp[1]);
	//printf("%s\n", data->envp[2]);
	//printf("%s\n", data->envp[3]);
	return (0);
}