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

char	*jwan(char *s1, char *s2, char *s3)
{
	char	*s;
	t_var	p;

	p.i = 0;
	p.j = 0;
	p.l = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	s = (char *)malloc(len(s1) + len(s2) + len(s3) + 1);
	if (!s)
		return (NULL);
	while (s1[p.i])
	{
		s[p.i] = s1[p.i];
		p.i++;
	}
	while (s2[p.j])
		s[p.i++] = s2[p.j++];
	while (s3[p.l])
		s[p.i++] = s3[p.l++];
	s[p.i] = '\0';
	return (free(s1), s);
}

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

void	join_diff(t_var *p)
{
	while (p->tmp->next && (p->tmp->type == VAR || p->tmp->type == WORD
			|| p->tmp->type == EXIT_ST || p->tmp->type == AMBG) && (p->tmp->next->type == WORD
			|| p->tmp->next->type == VAR || p->tmp->next->type == EXIT_ST || p->tmp->next->type == AMBG))
	{
		p->s = jwan(p->s, p->tmp->str, p->tmp->next->str);
		p->ii = is_in_out(p);
		if (p->tmp->next->next)
		{
			p->tmp = p->tmp->next->next;
			p->l = 1;
		}
		else
		{
			p->tmp = p->tmp->next;
			p->l = 2;
		}
	}
}

void	lst_join_u(t_var *p)
{
	join_diff(p);
	if (p->l == 1 && (p->tmp->type == VAR || p->tmp->type == WORD
			|| p->tmp->type == EXIT_ST || p->tmp->type == AMBG))
	{
		p->s = ft_strjoin(p->s, p->tmp->str);
		if (p->tmp->quote)
			p->j = p->tmp->quote;
	}
	if (p->tmp->type == AMBG || p->ii)
		ft_lstadd_back_cmd(&p->res, lst_new_cmd(p->s, AMBG, p->j, p->tmp->is));
	else
		ft_lstadd_back_cmd(&p->res, lst_new_cmd(p->s, WORD, p->j, p->tmp->is));
	if (p->tmp->type != VAR && p->tmp->type != WORD && p->tmp->type != EXIT_ST && p->tmp->type != AMBG)
		ft_lstadd_back_cmd(&p->res, lst_new_cmd(p->tmp->str, p->tmp->type,
				p->tmp->quote, p->tmp->is));
	p->i = 1;
}

void	lst_join_u1(t_var *p)
{
	if (!p->i)
		ft_lstadd_back_cmd(&p->res, lst_new_cmd(p->tmp->str, p->tmp->type,
				p->tmp->quote, p->tmp->is));
	p->i = 0;
	p->tmp = p->tmp->next;
}

t_cmd	*lst_join(t_cmd *cmd)
{
	t_var	p;

	p.res = NULL;
	p.tmp = cmd;
	p.i = 0;
	p.ii = 0;
	p.j = 0;
	if (!cmd)
		return (NULL);
	while (p.tmp->next)
	{
		p.s = ft_strdup("");
		if ((p.tmp->type == VAR || p.tmp->type == WORD || p.tmp->type == AMBG
				|| p.tmp->type == EXIT_ST) && (p.tmp->next->type == WORD
				|| p.tmp->next->type == VAR || p.tmp->next->type == EXIT_ST
				|| p.tmp->next->type == AMBG))
			lst_join_u(&p);
		else
			lst_join_u1(&p);
		free(p.s);
	}
	if (!p.i)
		ft_lstadd_back_cmd(&p.res, lst_new_cmd(p.tmp->str, p.tmp->type,
				p.tmp->quote, p.tmp->is));
	list_free(&cmd, ft_lstsize(cmd));
	return (p.res);
}
