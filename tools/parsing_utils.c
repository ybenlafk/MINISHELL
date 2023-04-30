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
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(">", OUT, 0));
		p->i++;
	}
	if (s[p->i] == '<' && red_checker(s, p->i))
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd("<", IN, 0));
		p->i++;
	}
	if (s[p->i] == '|' && red_checker(s, p->i))
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd("|", PIPE, 0));
		p->i++;
	}
}

char	*s_quote_trim(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = malloc(len(str) + 1);
	if (!s)
		return (NULL);
	while (str[i])
	{
		if (str[i] != 39)
			s[j++] = str[i];
		i++;
	}
	s[j] = '\0';
	return (free(str), s);
}

char	*d_quote_trim(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = malloc(len(str) + 1);
	if (!s)
		return (NULL);
	while (str[i])
	{
		if (str[i] != 34)
			s[j++] = str[i];
		i++;
	}
	s[j] = '\0';
	return (free(str), s);
}
