/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:52:02 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/03 14:01:46 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*sort_ex(t_env	**env)
{
	t_env	*t;
	t_env	*tp;
	t_env	*tmp;
	t_env	*new;

	t = *env;
	tp = NULL;
	tmp = t;
	new = NULL;
	if (!env)
		return (NULL);
	while (t)
	{
		ft_lstadd_back_env(&tp, lst_new_env(t->e, 0));
		t = t->next;
	}
	if (!tp)
		return (NULL);
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
		ft_lstdelone1(&tp, tmp->e);
		if (ft_lstsize_en(new) == ft_lstsize_en(*env))
			break ;
	}
	// fenv(env);
	// system("leaks minishell");
	fenv(&tp);
	return (new);
}

int	check_egl(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	puts("here-->");
	return (0);
}

void	norm_add(char *se, char *str, t_env	**env)
{
	int		i;
	char	*st;

	i = 0;
	while (str[i] != '=' && str[i])
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
