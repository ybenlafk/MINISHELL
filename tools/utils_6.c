/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/05/02 12:27:07 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	split_it(t_var *p, t_env *env)
{
	int		i;
	char	*s;

	s = set_value(env, p->s);
	if (!s)
		return (-1);
	p->str = ft_split(s, ' ');
	free(s);
	i = array_len(p->str);
	free(p->s);
	free_all(p->str);
	return (i);
}

int	ch_norm(t_var *p, t_env *env)
{
	p->s = NULL;
	get_var(p);
	if (p->s)
		return (split_it(p, env));
	return (-1);
}

void	where_norm(t_var *p, t_env *env)
{
	while (p->tmp && p->tmp->type != PIPE)
	{
		if (p->tmp->type == VAR)
			if (ch_norm(p, env) != 1)
				p->tmp->type = AMBG;
		if (p->tmp)
			p->tmp = p->tmp->next;
	}
}

int	where(t_var *p, t_env *env)
{
	while (p->tmp && p->tmp->type != PIPE)
	{
		if (p->tmp->type == OUT || p->tmp->type == APPEND || p->tmp->type == IN)
		{
			p->tmp = p->tmp->next;
			if (p->tmp && p->tmp->type == SPACE)
			{
				p->tmp = p->tmp->next;
				where_norm(p, env);
			}
			else
				where_norm(p, env);
		}
		if (p->tmp)
			p->tmp = p->tmp->next;
	}
	return (0);
}

int	check_exp(t_cmd *cmd, t_env *env)
{
	t_var	p;

	p.tmp = cmd;
	p.i = 0;
	while (p.tmp)
	{
		p.i = where(&p, env);
		if (p.tmp)
			p.tmp = p.tmp->next;
	}
	return (0);
}
