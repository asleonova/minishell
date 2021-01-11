/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:54:33 by monie             #+#    #+#             */
/*   Updated: 2021/01/11 18:54:43 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 1);
	g_error = 258;
	return (g_error);
}
