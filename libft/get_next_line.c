/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 18:49:38 by monie             #+#    #+#             */
/*   Updated: 2021/01/16 19:24:32 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char *s3;

	s3 = 0;
	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	else if (s1 && s2)
	{
		if (!(s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
			return (0);
		ft_strcpy_gnl(s3, s1);
		free(s1);
		ft_strcat_gnl(s3, s2);
	}
	return (s3);
}

int		output(char **line_left, char **line, int last_read)
{
	int		n;
	char	*tmp;

	if (last_read < 0)
		return (-1);
	if (*line_left && (n = ft_strchrn_gnl(*line_left, '\n')) >= 0)
	{
		(*line_left)[n] = '\0';
		*line = ft_strdup(*line_left);
		tmp = ft_strdup(*line_left + n + 1);
		free(*line_left);
		*line_left = tmp;
		return (1);
	}
	else if (*line_left)
	{
		*line = *line_left;
		*line_left = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		*line_left[MAX_FD];
	char			buf[BUFFER_SIZE + 1];
	int				last_read;
	int				n;
	char			*tmp;

	while ((last_read = read(fd, buf, BUFFER_SIZE)) != -1)
	{
		if (!last_read && line_left[0][0] == '\0')
			return (666);
		else if (!last_read)
			ft_putstr_fd("  \b\b", 1);
		buf[last_read] = '\0';
		line_left[fd] = ft_strjoin_gnl(line_left[fd], buf);
		if ((n = ft_strchrn_gnl(line_left[fd], '\n')) >= 0)
		{
			(line_left[fd])[n] = '\0';
			*line = ft_strdup(line_left[fd]);
			tmp = ft_strdup(line_left[fd] + n + 1);
			free(line_left[fd]);
			line_left[fd] = tmp;
			return (1);
		}
	}
	return (output(&line_left[fd], line, last_read));
}
