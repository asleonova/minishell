/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_initialization_clear.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 13:14:14 by monie             #+#    #+#             */
/*   Updated: 2021/01/16 16:40:08 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	var_initialization(t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->k = 0;
	var->error = 0;
	var->oq = ' ';
	var->q = 0;
	var->sq = 0;
	var->dq = 0;
	var->env = NULL;
	var->envf = 0;
	var->env_start = -1;
	var->env_end = -1;
	var->list = NULL;
	var->str = NULL;
	var->executor = 0;
	var->np = 0;
	var->flag = 0;
	var->invalid = 0;
	var->not_pack = 0;
	var->fq = ' ';
}

void	var_clear(t_var *var)
{
	free(var->str);
	var->str = NULL;
	free(var);
}
