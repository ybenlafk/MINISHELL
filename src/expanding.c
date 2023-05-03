/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:29:59 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/30 18:29:59 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_val_norm(char *s, t_var *p)
{
	p->i = 0;
	p->j = 0;
	while (s[p->i] && s[p->i] != '=')
		p->i++;
	if (s[p->i] != '=')
		return (1);
	p->i++;
	while (s[p->i] && s[p->i] != '\n')
	{
		p->i++;
		p->j++;
	}
	return (0);
}

char	*get_value(char *s)
{
	t_var	p;

	if (get_val_norm(s, &p))
		return (ft_strdup(""));
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

void	split_var(t_var *p, t_cmd **res, t_env *env)
{
	int		i;
	char	*s;

	s = set_value(env, p->s);
	if (!s)
		return ;
	i = 0;
	p->str = ft_split(s, ' ');
	free(s);
	free(p->s);
	if (p->str)
	{
		while (p->str[i])
		{
			ft_lstadd_back_cmd(res, lst_new_cmd(p->str[i++], WORD, 0, 0));
			if (p->str[i])
				ft_lstadd_back_cmd(res, lst_new_cmd(" ", SPACE, 0, 0));
		}
		free_all(p->str);
	}
}

int	exp_norm(t_var *p, t_cmd **res, t_env *env)
{
	if (p->tmp->type == VAR)
		get_var(p);
	if (p->s)
		split_var(p, res, env);
	else
		ft_lstadd_back_cmd(res, lst_new_cmd(p->tmp->str, p->tmp->type,
				p->tmp->quote, p->tmp->is));
	return (0);
}

t_cmd	*expanding(t_env *env, t_cmd *cmd)
{
	t_var	p;
	t_cmd	*res;

	res = NULL;
	p.tmp = cmd;
	while (p.tmp)
	{
		p.s = NULL;
		p.s1 = ft_itoa(g_var.g_exit_status);
		if (p.tmp->type == EXIT_ST)
			ft_lstadd_back_cmd(&res, lst_new_cmd(p.s1, p.tmp->type,
					p.tmp->quote, p.tmp->is));
		else
			exp_norm(&p, &res, env);
		free(p.s1);
		p.tmp = p.tmp->next;
	}
	list_free(&cmd, ft_lstsize(cmd));
	return (res);
}
