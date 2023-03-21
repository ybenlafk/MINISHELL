/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:43:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/21 10:44:56 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//print error.
void	error(char *e)
{
	printf("Minishell: syntax error near unexpected token `%s'\n", e);
}
// skip the spaces and return 1 if there is a spaces else return 0.
int	sps_skiper(char *s, int *i)
{
	int	stat;

	stat = 0;
	while (s[*i] && (s[*i] == '\t' || s[*i] == '\n' || s[*i] == '\v'
			|| s[*i] == '\f' || s[*i] == '\r' || s[*i] == ' '))
	{
		stat = 1;
		(*i)++;
	}
	if (stat)
		return (1);
	return (0);
}
// join the c character in the last of str.
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
	return (p.s);
}
// check the redirections.
int	redires_checker(t_cmd **list_cmd, char c1, char c2, int *i)
{
	if (!c1 || !c2)
		return (1);
	if (c1 == '<' && c2 == '<')
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd("<<", HEREDOC, 0, FALSE));
		*i += 2;
		return (0);
	}
	if (c1 == '>' && c2 == '>')
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(">>", APPEND, 0, FALSE));
		*i += 2;
		return (0);
	}
	return (1);
}
