/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:43:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/09 17:34:28 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error(char *e)
{
	g_var.g_exit_status = 258;
	printf("Minishell: syntax error near unexpected token `%s'\n", e);
}

int	sps_skiper(char *s, int *i)
{
	int	stat;

	stat = 0;
	while (s[*i] && is_white_sp(s[*i]))
	{
		stat = 1;
		(*i)++;
	}
	if (stat)
		return (1);
	return (0);
}

char	*char_join(char *str, char c)
{
	t_var	p;

	p.i = 0;
	p.len = 0;
	p.j = 0;
	p.len = len(str);
	p.s = malloc(p.len + 2);
	if (!p.s)
		return (NULL);
	while (p.i < p.len)
		p.s[p.j++] = str[p.i++];
	p.s[p.j++] = c;
	p.s[p.j] = '\0';
	return (free(str), p.s);
}

void	get_dil_util(t_var *p, t_cmd **list_cmd, char *s, int *i)
{
	p->j = 0;
	p->s1 = ft_strdup("");
	while (s[*i] && s[*i] != 39 && s[*i] != 34
		&& !is_white_sp(s[*i]) && !is_special_char(s[*i]))
	{
		p->s1 = char_join(p->s1, s[(*i)++]);
		p->j = 1;
	}
	if (p->j)
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s1, WORD, 0, 0));
		p->j = 0;
	}
	free(p->s1);
}

int	is_quoted(t_cmd **list_cmd, char *s, t_var *p, int *i)
{
	char	*str;

	str = NULL;
	if (s[*i] == 39)
	{
		str = is_quotes(s, i, 0);
		if (!str)
			return (1);
		p->w = s_quote_trim(str);
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->w, WORD, -1, 0));
		free(p->w);
	}
	if (s[*i] == 34)
	{
		str = is_quotes(s, i, 1);
		if (!str)
			return (1);
		p->w = d_quote_trim(str);
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->w, WORD, -1, 0));
		free(p->w);
	}
	return (0);
}
