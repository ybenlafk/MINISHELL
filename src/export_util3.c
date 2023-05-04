/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:52:02 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/03 23:47:27 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*norm_sort_ex(t_env *tp, t_env **env)
{
	t_env	*t;
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	t = *env;
	new = NULL;
	while (1)
	{
		t = tp;
		tmp = tp;
		while (t)
		{
			if (ft_strcmp(t->e, tmp->e) < 0)
				tmp = t;
			t = t->next;
		}
		ft_lstadd_back_env(&new, lst_new_env(tmp->e, 0));
		tp = ft_lstdelone(&tp, tmp->e);
		if (ft_lstsize_en(new) == ft_lstsize_en(*env))
			break ;
	}
	fenv(&tp);
	return (new);
}

t_env	*sort_ex(t_env	**env)
{
	t_env	*t;
	t_env	*tp;

	t = *env;
	tp = NULL;
	if (!env)
		return (NULL);
	while (t)
	{
		ft_lstadd_back_env(&tp, lst_new_env(t->e, 0));
		t = t->next;
	}
	if (!tp)
		return (NULL);
	return (norm_sort_ex(tp, env));
}

void	norm_add(char *se, char *str, t_env	**env)
{
	int		i;
	char	*st;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!check_egl(se))
	{
		st = ft_strjoin(ft_strdup(se), "=");
		st = ft_strjoin(st, str + (i + 1));
		ft_lstadd_back_env(env, lst_new_env(st, 0));
		free(st);
		*env = ft_lstdelone(env, se);
	}
	else
	{
		st = ft_strjoin(ft_strdup(se), str + (i + 1));
		ft_lstadd_back_env(env, lst_new_env(st, 0));
		free(st);
		*env = ft_lstdelone(env, se);
	}
}

void	add_plus(t_env **env, char *str, int i)
{
	int		j;
	t_env	*t;

	j = 1;
	t = *env;
	while (t)
	{
		if (j == i)
		{
			norm_add(t->e, str, env);
			break ;
		}
		t = t->next;
		j++;
	}
}

char	*del_plus(char *str)
{
	int		i;
	int		j;
	char	*st;

	i = 0;
	if (check_plus(str))
	{
		st = malloc(ft_strlen(str) - 1);
		if (!st)
			return (NULL);
	}
	else
		return (st = str, st);
	j = 0;
	while (str[i])
	{
		if (str[i] != '+')
			st[j++] = str[i++];
		else
			i++;
	}
	if (st[i] != '=')
		st[i++] = '=';
	st[i] = '\0';
	return (st);
}
