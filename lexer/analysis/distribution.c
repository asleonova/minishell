/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:22:23 by monie             #+#    #+#             */
/*   Updated: 2020/12/18 19:54:27 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	distribution_zero(t_syntax *syntax)
{
	if(syntax->ff == 1 || syntax->mf == 1 || \
		syntax->lf == 1 || syntax->pf == 1)
	{
		syntax->ff = 0;
		syntax->mf = 0;
		syntax->lf = 0;
		syntax->pf = 0;
	}
}

int		distribution(char *str, t_syntax *syntax, int i)
{
	distribution_zero(syntax);
	syntax->f = 0;
	if(str[i] == '$')
		syntax->envf = 1;
	else if(str[i] == '>' && str[i + 1] == '>')
		syntax->ff = 1;
	else if(str[i] == '>')
		syntax->mf = 1;
	else if(str[i] == '<')
		syntax->lf = 1;
	if(syntax->ff == 1 || syntax->mf == 1 || \
		syntax->lf == 1 || syntax->pf == 1)
		syntax->f = 1;
	if(syntax->f == 1)
		return(1);
	return(0);
}