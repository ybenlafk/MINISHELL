/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:03:19 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/20 12:31:35 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*is_var(char *s)
{
	t_var	p;

	p.i = 0;
	while (s[p.i] && s[p.i] != '=')
		p.i++;
	p.s = malloc(p.i + 1);
	if (!p.s)
		return (NULL);
	p.i = 0;
	while (s[p.i] && s[p.i] != '=')
	{
		p.s[p.i] = s[p.i];
		p.i++;
	}
	p.s[p.i] = 0;
	return (p.s);
}

char	*get_value(char *s)
{
	t_var	p;

	p.i = 0;
	p.j = 0;
	while (s[p.i] && s[p.i] != '=')
		p.i++;
	p.i++;
	while (s[p.i] && s[p.i] != '\n')
	{
		p.i++;
		p.j++;
	}
	p.s = malloc(p.j);
	if (!p.s)
		return (NULL);
	p.i = 0;
	p.j = 0;
	while (s[p.i] && s[p.i] != '=')
		p.i++;
	p.i++;
	while (s[p.i] && s[p.i] != '\n')
		p.s[p.j++] = s[p.i++];
	p.s[p.j] = 0;
	return (p.s);
}

char	*set_value(t_env *env, char *rep)
{
	t_var	p;

	p.i = 0;
	while (env)
	{
		p.s = is_var(env->e);
		if (!ft_strcmp(rep, p.s))
			return (get_value(env->e));
		env = env->next;
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

void	expanding(t_env *env, t_cmd *cmd)
{
	t_var	p;

	p.tmp = cmd;
	while (p.tmp)
	{
		p.s = NULL;
		if (p.tmp->type == VAR)
			get_var(&p);
		if (p.s)
			p.tmp->str = getenv(p.s);
		// if (p.s)
		// 	p.tmp->str = set_value(env, p.s);
		p.tmp = p.tmp->next;
	}
	p.tmp = cmd;
	quotes_expander(&p, p.tmp, env);
}
