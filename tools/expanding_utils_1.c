/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:18:21 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/07 02:23:01 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_back_exp(t_var *p, t_exp **exp)
{
	if (p->l && p->s)
	{
		ft_lstadd_back_exp(exp, lst_new_exp(p->s, 1));
		p->l = 0;
	}
	else if (p->s)
		ft_lstadd_back_exp(exp, lst_new_exp(p->s, 0));
}
int	utils_pro_max(char *s, t_var *p)
{
	if (s[p->i] == '$' && (!s[p->i + 1] || is_white_sp(s[p->i + 1])))
	{
		p->s = ft_strdup("$");
		p->i++;
		return (1) ;
	}
	if (s[p->i] == '$')
	{
		if (ft_isalpha(s[p->i + 1]) || s[p->i + 1] == '_')
			p->l = 1;
		else
			p->l = 0;
	}
	if (!p->l)
		return (p->i += 2, 1);
	if (len(p->s) >= 2 && !ft_isalnum(s[p->i]))
		return (1);
	p->s = char_join(p->s, s[p->i]);
	p->i++;
	if (s[p->i] == '$' && p->l)
        return (1);
	return (0);
}

void	vars_checker_pro_max(t_var *p, t_exp **exp, char *s)
{
	p->s = ft_strdup("");
	while (s[p->i] && s[p->i] != 39 && s[p->i] != 34 && !is_white_sp(s[p->i])
		&& !is_special_char(s[p->i]))
	{
		if (utils_pro_max(s, p))
			break ;
	}
	add_back_exp(p, exp);
	free(p->s);
}

void	words_checker_pro_max(t_var *p, t_exp **exp, char *s)
{
	p->s = ft_strdup("");
	while (s[p->i] && s[p->i] != '$')
	{
		p->s = char_join(p->s, s[p->i++]);
		p->j = 1;
	}
	if (p->j && p->s)
	{
		ft_lstadd_back_exp(exp, lst_new_exp(p->s, 0));
		p->j = 0;
	}
	free(p->s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	p = (char *)malloc(len(s1) + len(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

void	lexer_pro_max(t_exp **exp, char *s, t_var *p)
{
	p->i = 0;
	p->j = 0;
	p->l = 0;
	while (s[p->i])
	{
		words_checker_pro_max(p, exp, s);
		vars_checker_pro_max(p, exp, s);
	}
}
void	free_all(char **s)
{
	int i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

