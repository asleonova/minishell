/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 17:08:18 by monie             #+#    #+#             */
/*   Updated: 2021/01/11 19:10:34 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char			*ft_strcat(char *dest, const char *src);
//size_t			ft_strlen(const char *str);
int				ft_strchrn(char *s, int c);
char			*ft_strcpy(char *dst, const char *src);
//char			*ft_strdup(const char *src);
char			*ft_strjoin_gnl(char *s1, char *s2);
int				output(char **line_left, char **line, int last_read);
int				get_next_line(int fd, char **line);

# ifndef MAX_FD
#  define MAX_FD 256
# endif

//char	*ft_strdup_mod(const char *str, size_t n);
//int		get_next_line(int fd, char **line);

#endif
