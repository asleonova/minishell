/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:12:50 by dbliss            #+#    #+#             */
/*   Updated: 2021/01/09 12:13:14 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
	free(cwd);
	return (SUCCESS);
}
