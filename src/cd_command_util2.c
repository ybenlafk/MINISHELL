/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_util2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:22:33 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/03 15:09:24 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_path(t_env **env)
{
	char	*s1;
	char	*pwd;

	pwd = pwd_cmd();
	s1 = ft_strjoin(ft_strdup("PWD="), pwd);
	new_pwd(s1, env);
	g_var.g_exit_status = 0;
	free(s1);
	free(pwd);
}

void	old_pwd(char *str, t_env **env)
{
	t_env	*t;
	char	*st;

	t = *env;
	st = ft_strjoin(ft_strdup("OLDPWD="), str);
	while (t)
	{
		if (ft_strncmp("OLDPWD", t->e, 6) == 0)
		{
			ft_lstadd_back_env(env, lst_new_env(st, 0));
			*env = ft_lstdelone(env, t->e);
			break ;
		}
		t = t->next;
	}
	free(st);
}

char	*del_slash(char *str)
{
	char	*st;
	int		i;
	int		j;

	i = 0;
	j = 0;
	st = malloc(ft_strlen(str) + 1);
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] == '/')
			i++;
		st[j++] = str[i++];
	}
	st[j] = 0;
	return (st);
}

int	norm_check_pwd(t_env **env)
{
	t_env	*t;
	char	*s;

	t = *env;
	s = NULL;
	while (t)
	{
		s = is_var(t->e);
		if (ft_strcmp("OLDPWD", s) == 0)
			return (free(s), 1);
		t = t->next;
		free(s);
	}
	return (0);
}

int	check_pwd(t_env **env, char *str)
{
	t_env	*t;
	char	*s;

	t = *env;
	if (ft_strlen(str) == 3)
	{
		while (t)
		{
			s = is_var(t->e);
			if (ft_strcmp("PWD", s) == 0)
				return (free(s), 1);
			t = t->next;
			free(s);
		}
	}
	else
		if (norm_check_pwd(env))
			return (1);
	return (0);
}
