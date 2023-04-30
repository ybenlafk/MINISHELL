/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_util2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:22:33 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/30 17:19:03 by ybenlafk         ###   ########.fr       */
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
	gvar.g_exit_status = 0;
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
			ft_lstadd_back(env, ft_lstnew(st));
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

int	check_pwd(t_env **env, char *str)
{
	t_env	*t;

	t = *env;
	if (ft_strlen(str) == 3)
	{
		while (t)
		{
			if (ft_strncmp("PWD", t->e, 3) == 0)
				return (1);
			t = t->next;
		}
	}
	else
	{
		while (t)
		{
			if (ft_strncmp("OLDPWD", t->e, 6) == 0)
				return (1);
			t = t->next;
		}
	}
	return (0);
}

int	chech_directory(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) != 0)
		return (0);
	if (S_ISDIR(file_info.st_mode))
		return (1);
	if (S_ISREG(file_info.st_mode))
		return (2);
	return (0);
}
