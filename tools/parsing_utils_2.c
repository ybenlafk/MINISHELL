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

void	qutes_skiper(char *s, int *i, int type)
{
	int is;

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
	int i;

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
	t_var p;
	char *str;

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
