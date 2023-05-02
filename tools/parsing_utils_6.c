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

char	**env_geter(t_env *env)
{
	t_var	p;

	p.tmp_e = env;
	p.i = 0;
	p.str = malloc(sizeof(char *) * ft_lstsize_en(env) + 1);
	if (!p.str)
		return (NULL);
	while (p.tmp_e)
	{
		p.str[p.i++] = ft_strdup(p.tmp_e->e);
		p.tmp_e = p.tmp_e->next;
	}
	p.str[p.i] = NULL;
	return (p.str);
}

void	glob_init(void)
{
	g_var.g_exit_status = 0;
	g_var.err = 0;
	g_var.is = 0;
}
