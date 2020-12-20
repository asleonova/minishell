/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <dbliss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 19:42:10 by dbliss            #+#    #+#             */
/*   Updated: 2020/05/23 15:27:16 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			word_count(const char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		while (s[i + 1] && s[i] != c)
			i++;
		i++;
	}
	return (count);
}

static int			word_len(const char *s, char c)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static void			*free_tab(char **tab, int size)
{
	int i;

	i = 0;
	while (size > i)
		free(tab[i++]);
	free(tab);
	return (0);
}

char				**ft_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		len;
	int		count;

	if (!s || !(tab = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1))))
		return (NULL);
	i = 0;
	count = 0;
	while (i < word_count(s, c))
	{
		len = word_len(&s[count], c);
		if (!(tab[i] = (char *)malloc(sizeof(char) * (len + 1))))
			free_tab(tab, count);
		j = 0;
		while (s[count] == c)
			count++;
		while (s[count] != c && s[count])
			tab[i][j++] = s[count++];
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
