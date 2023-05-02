/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/10 17:43:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 15:56:54 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_out(t_var *p)
{
	if (p->tmp->quote == 1 || p->tmp->next->quote == 1)
		p->j = 1;
	else if (p->tmp->quote == 2 || p->tmp->next->quote == 2)
		p->j = 2;
	else if (p->tmp->quote == -1 || p->tmp->next->quote == -1)
		p->j = -1;
	if (p->tmp->type == AMBG || p->tmp->next->type == AMBG)
		return (1);
	return (0);
}