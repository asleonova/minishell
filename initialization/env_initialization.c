/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 12:10:27 by monie             #+#    #+#             */
/*   Updated: 2021/01/03 17:02:08 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_initialization(t_env *tmp)
{
	tmp->i = 0;
	tmp->j = 0;
	tmp->k = 0;
	tmp->end = 0;
	tmp->env = NULL;
	tmp->str = NULL;
}

void	env_initialization_step(t_env *tmp)
{
	tmp->end = tmp->i;
	tmp->i = 0;
	tmp->j = 0;
	tmp->k = 0;
}
