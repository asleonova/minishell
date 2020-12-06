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

int			unset_env(t_data *main, char *arg)
{
	char	**temp;
	char	**ptr;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = 0;
	len = tab_len(main->envp);
	temp = (char **)malloc((len) * sizeof(char *));
	while (++i < len)
	{
		ptr = ft_split(main->envp[i], '=');
		if (ft_strncmp(ptr[0], arg, -1) == 0)
		{
			free_tab(ptr);
			continue ;
		}
		free_tab(ptr);
		temp[j++] = ft_strdup(main->envp[i]);
	}
	temp[j] = 0;
	free_tab(main->envp);
	main->envp = temp;
	return (1);
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

void		add_env_var(char *str, t_data *data)
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
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	free_tab(data->envp);
	data->envp = tmp;
}

char *get_env_values(char *key, t_data *data)
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

void	ft_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
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

void		ft_unset_env(char *str, t_data *data)
{
	char	*tmp;

		if ((tmp = get_env_values(str, data)) != NULL)
		{
			free(tmp);
			delete_env_var(str, data);
		}
}

void ft_export_update(t_data *data, char *str) // это поменять значение уже существующей переменной
{
	char	**temp;

	temp = ft_split(str, '=');
	ft_unset_env(temp[0], data);
	free_tab(temp);
	add_env_var(str, data);
}

int			ft_export(t_data *data, t_commands *command)
{
	if (command->count_args == 0)
	{
		ft_print_export(data);
		return(SUCCESS);
	}
	while (command->lst)
	{
		ft_export_update(data, command->lst->content);
		command->lst = command->lst->next;
	}
	ft_print_export(data);
	return(SUCCESS);
}

int main() // testing unset env func
{
	t_data *data;
	t_commands *command;
	
	// char *str;
	data = malloc(sizeof(t_data));
	command = malloc(sizeof(t_commands));
	command->count_args = 1;
	// str = malloc(sizeof(char) * 4);
	data->envp = (char**)malloc(sizeof(char *) * 4 + 1);
	data->envp[0] = ft_strdup("ZSHC=/Users/dbliss/.oh-my-zsh");
	data->envp[1] = ft_strdup("CSERR=dbliss");
	data->envp[2] = ft_strdup("anna=");
	data->envp[3] = ft_strdup("sfkjsfklfsjl=flsfl");
	data->envp[4] = NULL;
	command->lst = ft_lstnew("dZSHC=dffsd");
	append_lst(&command->lst, "heeeey");
	append_lst(&command->lst, "heeeey=");
	printf("\n\n----PRINT LST----\n\n");
	printf("%s\n", command->lst->content);
	printf("%s\n", command->lst->next->content);
	printf("%s\n", command->lst->next->next->content);
	printf("\n\n----LST END----\n\n");
	// str = "USER";
	printf("%s\n", data->envp[0]);
	printf("%s\n", data->envp[1]);
	printf("%s\n", data->envp[2]);
	printf("%s\n", data->envp[3]);
	
	// delete_env_var(str, data);
	// printf("\n\n----UNSET VERSION----\n\n");
	printf("\n\n----PRINT EXPORT----\n\n");
	ft_export(data, command);
	return (0);
}
