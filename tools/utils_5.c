/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/30 18:28:34 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalpha(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	return (0);
}

void	fenv(t_env **env)
{
	t_env	*p1;
	t_env	*p;

	p1 = *env;
	while (p1)
	{
		free(p1->e);
		p = p1;
		p1 = p1->next;
		free(p);
		p = NULL;
	}
	env = NULL;
}

char	*set_value(t_env *env, char *rep)
{
	t_var	p;

	p.i = 0;
	while (env)
	{
		p.s = is_var(env->e);
		if (!ft_strcmp(rep, p.s))
			return (free(p.s), get_value(env->e));
		env = env->next;
		free(p.s);
	}
	return (ft_strdup(""));
}

void	get_var(t_var *p)
{
	p->j = 0;
	p->i = 0;
	while (p->tmp->str[p->i] && !is_special_char(p->tmp->str[p->i]))
	{
		if ((p->tmp->str[p->i] == '$') && (ft_isalpha(p->tmp->str[p->i + 1])
				|| p->tmp->str[p->i + 1] == '_'))
		{
			p->j = 1;
			p->i++;
		}
		if ((p->j) && p->tmp->str[p->i] != '$' && (ft_isalnum(p->tmp->str[p->i])
				|| p->tmp->str[p->i] == '_'))
			p->s = char_join(p->s, p->tmp->str[p->i]);
		else if (p->j)
			break ;
		p->i++;
	}
}
