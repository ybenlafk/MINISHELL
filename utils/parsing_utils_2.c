/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:43:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/17 19:17:58 by ybenlafk         ###   ########.fr       */
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
		if (is == 2)
			break ;
	}
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
			return (quote_trim(str));
	}
	if (!stat)
		return (error("'"), NULL);
	return (error("\""), NULL);
}

int	quotes_checker(t_cmd **list_cmd, char *s, t_var *p)
{
	p->j = 0;
	if (s[p->i] == 39)
	{
		p->s = is_quotes(s, &p->i, 0);
		if (!p->s)
			return (1);
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, WORD, 1));
	}
	if (s[p->i] == 34)
	{
		p->s = is_quotes(s, &p->i, 1);
		if (!p->s)
			return (1);
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, WORD, 2));
	}
	return (0);
}

void	add_back(t_var *p, t_cmd **list_cmd)
{
	if (p->l)
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, VAR, 0));
		p->l = 0;
	}
	else if (p->s)
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, WORD, 0));
}

void	vars_checker(t_var *p, t_cmd **list_cmd, char *s)
{
	p->s = NULL;
	while (s[p->i] && s[p->i] != 39 && s[p->i] != 34 && s[p->i] != ' '
		&& !is_special_char(s[p->i]))
	{
		if (s[p->i] == '$' && !s[p->i + 1])
		{
			p->s = ft_strdup("$");
			p->i++;
			break ;	
		}
		if (s[p->i] == '$')
		{
			if (ft_isalpha(s[p->i + 1]) || s[p->i + 1] == '_')
				p->l = 1;
			else
				p->l = 0;
		}
		if (!p->l)
		{
			p->i += 2;
			break;
		}
		if (len(p->s) >= 2 && !ft_isalnum(s[p->i]))
			break;
		p->s = char_join(p->s, s[p->i]);
		p->i++;
		if (s[p->i] == '$' && p->l)
            break;
	}
	add_back(p, list_cmd);
}

void	words_checker(t_var *p, t_cmd **list_cmd, char *s)
{
	p->j = 0;
	p->s = NULL;
	while (s[p->i] && s[p->i] != 39 && s[p->i] != 34 && s[p->i] != '$'
		&& s[p->i] != ' ' && !is_special_char(s[p->i]))
	{
		p->s = char_join(p->s, s[p->i++]);
		p->j = 1;
	}
	if (p->j)
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, WORD, 0));
		p->j = 0;
	}
}
