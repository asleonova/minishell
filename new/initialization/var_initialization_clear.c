/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_initialization_clear.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 13:14:14 by monie             #+#    #+#             */
/*   Updated: 2020/12/20 17:20:55 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void var_initialization(t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->k = 0;
	var->error = 0;
	var->rf = 0;
	var->df = 0;
	var->rif = 0;
}

void var_clear(t_var *var)
{
	free(var->str);
	var->str = NULL;
}