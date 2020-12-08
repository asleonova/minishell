#include <unistd.h>
#include "minishell.h"
#include <stdio.h>

void append_lst(t_list **lst, void *new_content) 
{ 
    /* 1. allocate node */
    t_list *new_node;
	t_list *last;
	
	new_node = malloc(sizeof(t_list)); 
	last = *lst;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->content  = new_content; 
  
    /* 3. This new node is going to be the last node, so make next of 
          it as NULL*/
    new_node->next = NULL; 
  
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*lst == NULL) 
    { 
       *lst = new_node; 
       return; 
    } 
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL) 
        last = last->next; 
  
    /* 6. Change the next of last node */
    last->next = new_node; 
    return; 
}

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
void	update_env_var(char *var, t_data *data)
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

void		ft_unset_env(char *str, t_data *data)
{
	char	*tmp;

		if ((tmp = get_env_values(data, str)) != NULL) // если у нас есть значение у п.о. PATH="hello"
		{
			free(tmp);
			update_env_var(str, data);
		}
}

int error_identifier(t_commands *command)
{
	ft_putstr_fd("minishell: unset: `", 1);
	ft_putstr_fd(command->lst->content, 1);
	ft_putstr_fd("\' : not a valid identifier", 1);
	ft_putchar_fd('\n', 1);
	return(FAIL);
}


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