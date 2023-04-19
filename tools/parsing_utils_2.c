/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:43:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 15:56:54 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	qutes_skiper(char *s, int *i, int type)
{
	int	is;

	is = 0;
	while (s[*i])
	{
		if (s[*i] == type)
			is++;
		else
			break ;
		(*i)++;
		if (!s[*i])
			break ;
		if (is == 2)
			break ;
	}
}

int	is_white_sp(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f'
		|| c == '\n')
		return (1);
	return (0);
}

int	check_or(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		qutes_skiper(s + i, &i, 34);
		qutes_skiper(s + i, &i, 39);
		if (s[i] == c && s[i + 1] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*is_quotes(char *s, int *i, int stat)
{
	t_var	p;
	char	*str;

	p.j = 0;
	if (!stat)
		p.i = 39;
	else
		p.i = 34;
	str = NULL;
	while (s[*i])
	{
		if (s[*i] == p.i)
			p.j++;
		str = char_join(str, s[*i]);
		(*i)++;
		if (p.j == 2)
			return (str);
	}
	if (!stat)
		return (error("'"), free(str), NULL);
	return (error("\""), free(str), NULL);
}
int	quotes_checker(t_cmd **list_cmd, char *s, t_var *p)
{
	p->j = 0;
	p->s = NULL;
	if (s[p->i] == 39)
	{
		p->s = is_quotes(s, &p->i, 0);
		if (!p->s)
			return (1);
		p->w = s_quote_trim(p->s);
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->w, WORD, 1));
		free(p->w);
	}
	if (s[p->i] == 34)
	{
		p->s = is_quotes(s, &p->i, 1);
		if (!p->s)
			return (1);
		p->w = d_quote_trim(p->s);
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->w, WORD, 2));
		free(p->w);
	}
	return (0);
}

void	add_back(t_var *p, t_cmd **list_cmd)
{
	if (p->l)
	{
		if (!ft_strcmp(p->s, "$?"))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, EXIT_ST, 0));
		else
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, VAR, 0));
		p->l = 0;
	}
	else if (p->s[0])
	{
		if (!ft_strcmp(p->s, "$?"))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, EXIT_ST, 0));
		else
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, WORD, 0));
	}
}

int	vars_checker_util(char *s, t_var *p)
{
	if (s[p->i] == '$' && s[p->i + 1] == '?')
		return (p->s = ft_strdup("$?"), p->i += 2, 1);
	if (s[p->i] == '$' && (!s[p->i + 1] || is_white_sp(s[p->i + 1])))
	{
		p->s = ft_strdup("$");
		p->i++;
		return (1);
	}
	if (s[p->i] == '$')
	{
		if (ft_isalpha(s[p->i + 1]) || s[p->i + 1] == '_')
			p->l = 1;
		else
			p->l = 0;
	}
	if (!p->l && s[p->i + 1] != 34 && s[p->i + 1] != 39)
		return (p->i += 2, 1);
	else if (!p->l && (s[p->i + 1] == 34 || s[p->i + 1] == 39))
		return (p->i++, 1);
	if (len(p->s) >= 2 && !ft_isalnum(s[p->i]))
		return (1);
	p->s = char_join(p->s, s[p->i]);
	p->i++;
	if (s[p->i] == '$' && p->l)
		return (1);
	return (0);
}

void	vars_checker(t_var *p, t_cmd **list_cmd, char *s)
{
	p->s = ft_strdup("");
	while (s[p->i] && s[p->i] != 39 && s[p->i] != 34 && !is_white_sp(s[p->i])
		&& !is_special_char(s[p->i]))
		if (vars_checker_util(s, p))
			break ;
	add_back(p, list_cmd);
	free(p->s);
}

void	words_checker(t_var *p, t_cmd **list_cmd, char *s)
{
	p->j = 0;
	p->s = ft_strdup("");
	while (s[p->i] && s[p->i] != 39 && s[p->i] != 34 && s[p->i] != '$'
		&& !is_white_sp(s[p->i]) && !is_special_char(s[p->i]))
	{
		p->s = char_join(p->s, s[p->i++]);
		p->j = 1;
	}
	if (p->j)
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, WORD, 0));
		p->j = 0;
	}
	free(p->s);
}

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

void	join_diff(t_var *p)
{
	while (p->tmp->next && (p->tmp->type == VAR || p->tmp->type == WORD || p->tmp->type == EXIT_ST)
		&& (p->tmp->next->type == WORD || p->tmp->next->type == VAR))
	{
		p->s = jwan(p->s, p->tmp->str, p->tmp->next->str);
		if (p->tmp->quote == 1 || p->tmp->next->quote == 1)
			p->j = 1;
		else if (p->tmp->quote == 2 || p->tmp->next->quote == 2)
			p->j = 2;
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
	if (p->l == 1 && (p->tmp->type == VAR
			|| p->tmp->type == WORD || p->tmp->type == EXIT_ST))
		p->s = ft_strjoin(p->s, p->tmp->str);
	ft_lstadd_back_cmd(&p->res, lst_new_cmd(p->s, WORD, p->j));
	if (p->tmp->type != VAR && p->tmp->type != WORD && p->tmp->type != EXIT_ST)
		ft_lstadd_back_cmd(&p->res, lst_new_cmd(p->tmp->str, p->tmp->type,
				p->tmp->quote));
	p->i = 1;
}

void	lst_join_u1(t_var *p)
{
	if (!p->i)
		ft_lstadd_back_cmd(&p->res, lst_new_cmd(p->tmp->str, p->tmp->type,
				p->tmp->quote));
	p->i = 0;
	p->tmp = p->tmp->next;
}

t_cmd	*lst_join(t_cmd *cmd)
{
	t_var	p;

	p.res = NULL;
	p.tmp = cmd;
	p.i = 0;
	if (!cmd)
		return (NULL);
	while (p.tmp->next)
	{
		p.s = ft_strdup("");
		if ((p.tmp->type == VAR || p.tmp->type == WORD || p.tmp->type == EXIT_ST) 
			&& (p.tmp->next->type == WORD || p.tmp->next->type == VAR || p.tmp->next->type == EXIT_ST))
			lst_join_u(&p);
		else
			lst_join_u1(&p);
		free(p.s);
	}
	if (!p.i)
		ft_lstadd_back_cmd(&p.res, lst_new_cmd(p.tmp->str, p.tmp->type, p.tmp->quote));
	list_free(&cmd, ft_lstsize(cmd));
	return (p.res);
}
//ls<<c"   "<<d