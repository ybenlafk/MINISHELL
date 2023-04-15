/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:18:21 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 18:15:52 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_exp	*ft_lstlast_exp(t_exp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_exp(t_exp **lst, t_exp *new)
{
	t_exp	*p;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			p = ft_lstlast_exp(*lst);
			p->next = new;
		}
	}
}

t_exp	*lst_new_exp(char *value, int stat)
{
	t_exp	*new;

	new = malloc(sizeof(t_exp));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->stat = stat;
	new->next = NULL;
	return (new);
}

void	get_var_pro_max(t_var *p)
{
	p->i = 0;
	p->is = 1;
	while (p->tmp->str[p->i] && !is_special_char(p->tmp->str[p->i]))
	{
		if ((p->tmp->str[p->i] == '$') && (ft_isalpha(p->tmp->str[p->i + 1])
				|| p->tmp->str[p->i + 1] == '_'))
		{
			p->j = 1;
			p->is = 0;
			p->i++;
		}
		if ((p->j) && p->tmp->str[p->i] != '$' && (ft_isalnum(p->tmp->str[p->i])
				|| p->tmp->str[p->i] == '_'))
			p->s = char_join(p->s, p->tmp->str[p->i]);
		else if (p->j)
			break ;
		p->i++;
	}
}

char	*check_set(t_exp *exp, t_env *env)
{
	char	*s;
	char	*res;
	t_exp	*tmp;

	if (!env)
		return (NULL);
	tmp = exp;	
	res = ft_strdup("");
	while (tmp)
	{
		if (tmp->stat)
		{
			if (tmp->stat == 1)
				s = set_value(env, tmp->value + 1);
			else
				s = ft_itoa(g_exit_status);
			res = ft_strjoin(res, s);
			free(s);
		}
		else
			res = ft_strjoin(res, tmp->value);
		tmp = tmp->next;
	}
	return (res);
}
int	ft_lstsize_exp(t_exp *lst)
{
	t_exp	*tmp;
	int		len;

	tmp = lst;
	len = 0;
	if (!tmp)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
void	free_exp(t_exp **cmd, int len)
{
	t_exp	*tmp;

	while (len--)
	{
		tmp = (*cmd);
		*cmd = (*cmd)->next;
		free(tmp->value);
		free(tmp);
	}
}

void	quotes_expander(t_cmd *cmd, t_env *env)
{
	t_var 	p;
	t_exp	*exp;
	char	*s;

	p.i = 0;
	p.j = 0;
	p.is = 1;
	p.tmp = cmd;
	while (p.tmp)
	{
		if (p.tmp->quote == 2)
		{
			exp = NULL;
			lexer_pro_max(&exp, p.tmp->str, &p);
			s = check_set(exp, env);
			free(p.tmp->str);
			p.tmp->str = ft_strdup(s);
			free(s);
			free_exp(&exp, ft_lstsize_exp(exp));
		}
		p.tmp = p.tmp->next;
	}
}