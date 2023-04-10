/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:03:19 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 16:05:12 by nouahidi         ###   ########.fr       */
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
			return (free(p.s), get_value(env->e));
		env = env->next;
		free(p.s);
	}
	return (NULL);
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

void	split_var(t_var *p, t_cmd **res, t_env *env)
{
	int 	i;
	char	*s;

	s = set_value(env, p->s);
	if (!s)
		return;
	i = 0;
	p->str = ft_split(s, ' ');
	free(s);
	free(p->s);
	if (p->str)
	{
		while (p->str[i])
		{
			ft_lstadd_back_cmd(res, lst_new_cmd(p->str[i++], WORD, 0));
			if (p->str[i])
				ft_lstadd_back_cmd(res, lst_new_cmd(" ", SPACE, 0));
		}	
		free_all(p->str);
	}
}

t_cmd	*expanding(t_env *env, t_cmd *cmd)
{
	t_var	p;
	t_cmd *res;

	res = NULL;
	p.tmp = cmd;
	while (p.tmp)
	{
		p.s = NULL;
		if (p.tmp->type == VAR)
			get_var(&p);
		if (p.s)
			split_var(&p, &res, env);
		if (p.tmp->type == EXIT_ST)
			ft_lstadd_back_cmd(&res, lst_new_cmd(ft_itoa(exit_status), p.tmp->type, p.tmp->quote));
		else 
			ft_lstadd_back_cmd(&res, lst_new_cmd(p.tmp->str, p.tmp->type, p.tmp->quote));
		p.tmp = p.tmp->next;
	}
	list_free(&cmd, ft_lstsize(cmd));
	return (res);
}
