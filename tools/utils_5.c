/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/05/01 20:12:32 by ybenlafk         ###   ########.fr       */
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

int	array_len(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	split_it(t_var *p, t_env *env)
{
	int		i;
	char	*s;

	s = set_value(env, p->s);
	p->s1 = ft_strdup(s);
	if (!s)
		return(-1);
	p->str = ft_split(s, ' ');
	free(s);
	i = array_len(p->str);
	// free(p->s);
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
		{
			if (ch_norm(p, env) != 1)
			{
				p->tmp->type = AMBG;
				free(p->s1);
				free(p->s);
			}
		}
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

void	del_gus(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	g_var.err--;
	while (tmp && g_var.err--)
		tmp = tmp->next;
	tmp->is = 1;
}