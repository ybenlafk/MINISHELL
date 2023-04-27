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

//print error.
void	error(char *e)
{
	gvar.g_exit_status = 258;
	printf("Minishell: syntax error near unexpected token `%s'\n", e);
}
// skip the spaces and return 1 if there is a spaces else return 0.
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
	return (free(str), p.s);
}

void	get_dil_util(t_var *p, t_cmd **list_cmd, char *s, int *i)
{
	p->j = 0;
	p->s = ft_strdup("");
	while (s[*i] && s[*i] != 39 && s[*i] != 34
		&& !is_white_sp(s[*i]) && !is_special_char(s[*i]))
	{
		p->s = char_join(p->s, s[(*i)++]);
		p->j = 1;
	}
	if (p->j)
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(p->s, WORD, 0));
		p->j = 0;
	}
	free(p->s);
}

int	get_dilemiter(t_cmd **list_cmd, char *s, int *i)
{
	t_var p;
	
	p.i = 0;
	p.s = ft_strdup("");
	if (sps_skiper(s, i))
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0));
	if (quotes_checker(list_cmd, s, &p))
		return (1);
	get_dil_util(&p, list_cmd, s, i);
	return (0);
}

// check the redirections.
int	redires_checker(t_cmd **list_cmd, char *s, int *i)
{
	if (!s[*i] || !s[*i + 1])
		return (0);
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd("<<", HEREDOC, 0));
		*i += 2;
		if (get_dilemiter(list_cmd, s, i))
			return (1);
	}
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(">>", APPEND, 0));
		*i += 2;
	}
	return (0);
}
