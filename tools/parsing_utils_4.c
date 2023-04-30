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
		return (free(p->s), p->s = ft_strdup("$?"), p->i += 2, 1);
	if (s[p->i] == '$' && (!s[p->i + 1] || is_white_sp(s[p->i + 1])))
	{
		free(p->s);
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
