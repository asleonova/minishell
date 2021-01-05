/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monie <monie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 13:29:41 by monie             #+#    #+#             */
/*   Updated: 2021/01/02 13:06:05 by monie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_list(t_var *var)
{
	ft_lstadd_back(&(var->list), ft_lstnew(ft_strdup(var->arr)));
}

void create_lexer(t_var *var, int i)
{
 var->arr = malloc(var->j - var->k + 1);
 if (var->arr == NULL)
  var->error = 1;
 while (var->k < var->j)
 {
  if (var->str[var->k] == '\'' || var->str[var->k] == '"')
  {
   if(var->oq != '\'' && var->oq != '"')
    var->oq = (var->str[var->k] == '\'') ? '\'' : '"';
   if(var->oq == var->str[var->k])
    var->k++;
  }
  var->arr[i++] = var->str[var->k++];
 }
 var->arr[i] = '\0';
 create_list(var);
 free(var->arr);
 var->arr = NULL;
}
