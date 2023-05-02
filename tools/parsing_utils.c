/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:38:12 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/05 23:49:03 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_char(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	red_checker(char *s, int i)
{
	if (!s[i] || !s[i + 1])
		return (1);
	if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i + 1] == '>'))
		return (0);
	return (1);
}

void	add_special_char(char *s, t_cmd **list_cmd, t_var *p)
{
	if (s[p->i] == '>' && red_checker(s, p->i))
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(">", OUT, 0, 0));
		p->i++;
	}
	if (s[p->i] == '<' && red_checker(s, p->i))
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd("<", IN, 0, 0));
		p->i++;
	}
	if (s[p->i] == '|' && red_checker(s, p->i))
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd("|", PIPE, 0, 0));
		p->i++;
	}
}

char	*s_quote_trim(char *str)
{
	t_var	p;

	p.i = 0;
	p.j = 0;
	p.l = 0;
	while (str[p.i])
		if (str[p.i++] == 39)
			p.l++;
	p.s = malloc((len(str) - p.l) + 1);
	if (!p.s)
		return (NULL);
	p.i = 0;
	while (str[p.i])
	{
		if (str[p.i] != 39)
			p.s[p.j++] = str[p.i];
		p.i++;
	}
	p.s[p.j] = '\0';
	return (free(str), p.s);
}

char	*d_quote_trim(char *str)
{
	t_var	p;

	p.i = 0;
	p.j = 0;
	p.l = 0;
	while (str[p.i])
		if (str[p.i++] == 34)
			p.l++;
	p.s = malloc((len(str) - p.l) + 1);
	if (!p.s)
		return (NULL);
	p.i = 0;
	while (str[p.i])
	{
		if (str[p.i] != 34)
			p.s[p.j++] = str[p.i];
		p.i++;
	}
	p.s[p.j] = '\0';
	return (free(str), p.s);
}
