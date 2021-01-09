/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:14:13 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/09 12:15:13 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int			tab_len(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

void		ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void		ft_sort_list(t_data *data)
{
	int	i;
	int	j;
	int	len;
	int	diff;

	i = 0;
	len = tab_len(data->envp);
	while (i < len - 1)
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
