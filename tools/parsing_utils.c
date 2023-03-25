/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:38:12 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/24 17:40:59 by ybenlafk         ###   ########.fr       */
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

void	add_special_char(char c1, char c2, t_cmd **list_cmd, t_var *p)
{
	if (c1 == '>' && redires_checker(list_cmd, c1, c2, &p->i))
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(char_to_str(c1), OUT, 0));
		p->i++;
	}
	if (c1 == '<' && redires_checker(list_cmd, c1, c2, &p->i))
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(char_to_str(c1), IN, 0));
		p->i++;
	}
	if (c1 == '|' && redires_checker(list_cmd, c1, c2, &p->i))
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(char_to_str(c1), PIPE, 0));
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

char	*char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
