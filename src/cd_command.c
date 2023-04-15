/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:24:06 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/10 18:00:15 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	old_pwd(char *str, t_env **env)
{
	t_env	*t;
	int		i;
	char	*st;

	t = *env;
	st = ft_strjoin("OLDPWD=", str);
	while (t)
	{
		if (ft_strncmp("OLDPWD=", t->e, 6) == 0)
		{
			ft_lstadd_back(env, ft_lstnew(st));
			*env = ft_lstdelone(env, t->e);
			break ;
		}
		t = t->next;
	}
}

char	*del_slash(char *str)
{
	char	*st;
	int		i;
	int		j;

	i = 0;
	j = 0;
	st = malloc(ft_strlen(str));
	if (!str)
		return (0);
	while (str[i])
	{
		st[j++] = str[i++];
		if (str[i] == '/' && str[i + 1] == '/')
			i++;
	}
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

char	*new_pwd_norm(t_env **env, char	*str)
{
	t_env	*t;

	t = *env;
	while (t)
	{
		if (ft_strncmp("PWD=", t->e, 3) == 0)
		{
			if (!ft_strcmp(ft_strjoin("PWD=", "/"), t->e)
				&& !ft_strcmp(ft_strjoin("PWD=", "/"), str))
				break ;
			ft_lstadd_back(env, ft_lstnew(str));
			*env = ft_lstdelone(env, t->e);
			break ;
		}
		t = t->next;
	}
	return (t->e);
}

void	new_pwd(char *str, t_env **env)
{
	t_env	*t;
	char	*st;

	t = *env;
	str = del_slash(str);
	if (check_pwd(env, "PWD"))
		st = new_pwd_norm(env, str);
	if (check_pwd(env, "OLDPWD"))
	{
		if (check_pwd(env, "PWD"))
			old_pwd(st + 4, env);
		else
			old_pwd("", env);
	}
}

char	*change_dr(char	*str)
{
	int		i;
	int		j;
	char	*st;

	i = 0;
	while (str[i])
		i++;
	j = i;
	while (str[j] != '/' )
		j--;
	if (j == 0)
		return ("/");
	j = i - j;
	st = malloc(j);
	i = 0;
	while (j > i)
	{
		st[i] = str[i];
		i++;
	}
	st[i] = '\0';
	return (st);
}

char	*new_dr(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, "/");
	str = ft_strjoin(str, s2);
	return (str);
}

char *get_home(t_env **env)
{
	t_env	*t;

	t = *env;
	while (t)
	{
		if (!ft_strncmp("HOME", t->e, 4))
			return (t->e + 5);
		t = t->next;
	}
	return (NULL);
}

void	*search_oldpath(t_env	**env)
{
	t_env	*t;

	t = *env;
	while (t)
	{
		if (!ft_strncmp("PWD=", t->e, 4))
			return (t->e + 4);
		t = t->next;
	}
	return (get_home(env));
}

char	*del_dr(char *str)
{
	int		i;
	int		j;
	char	*st;

	i = ft_strlen(str);
	j = i;
	while (i >= 0)
	{
		if (str[i] == '/')
			break ;
		i--;
	}
	i--;
	st = malloc(i + 1);
	j = 0;
	while (j <= i)
	{
		st[j] = str[j];
		j++;
	}
	st[j] = '\0';
	return (st);
}

int	new_path(char	*str)
{
	int i = 0;
	while (i < 4)
	{
		if (chdir(str) != -1)
			return (1);
		else
			str = del_dr(str);
		i++;
	}
	return (0);
}

int	norm_cd(t_list	*lst, t_env	**env, char *str)
{
	char			*pwd_path;
	static int		i;
	char			*st;

	if (!str && !ft_strcmp("..", lst->args[1]))
	{
		if (i == 0)
		{
			ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", lst->out);
			i++;
			return (0);
		}
		else
		{
			pwd_path = search_oldpath(env);
			if (!new_path(pwd_path))
			{
				ft_putstr_fd("HOME not set\n", lst->out);
				return (0);
			}
		}
		st = ft_strjoin("PWD=", pwd_cmd());
		new_pwd(st, env);
		return (0);
	}
	return (1);
}

void	cd_cmd(t_list *lst, t_env **env)
{
	char			*str;
	char			*st;

	str = pwd_cmd();
	if (!lst->args[1])
	{
		if (chdir(get_home(env)) == -1)
			ft_putstr_fd("Minishell>$ cd: HOME not set\n", lst->out);
		return ;
	}
	if (!str && !ft_strcmp(".", lst->args[1]))
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", lst->out);
		return ;
	}
	if (!norm_cd(lst, env, str))
		return ;
	if (chdir(lst->args[1]) != 0)
		printf("Minishell>$ cd: %s: No such file or directory\n", lst->args[1]);
	else
	{
		st = ft_strjoin("PWD=", pwd_cmd());
		new_pwd(st, env);
	}
}
