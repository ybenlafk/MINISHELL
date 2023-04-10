/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:24:06 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/10 14:45:03 by nouahidi         ###   ########.fr       */
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

void	new_pwd(char *str, t_env **env)
{
	t_env	*t;

	t = *env;
	str = del_slash(str);
	if (check_pwd(env, "PWD"))
	{
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
	}
	if (check_pwd(env, "OLDPWD"))
	{
		if (check_pwd(env, "PWD"))
			old_pwd(t->e + 4, env);
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

void	cd_cmd(t_list *lst, t_env **env)
{
	char	*str;
	char	*st;
	char	**tab;
	int		i;
	int		j;

	i = 0;
	tab = ft_split(lst->args[1], '/');
	str = pwd_cmd();
	if (!lst->args[1])
	{
		chdir("/Users/nouahidi");
		new_pwd("PWD=/Users/nouahidi", env);
		return ;
	}
	while (tab[i])
	{
		if (lst->args[1][0] == '/')
			str = lst->args[1];
		else if (!ft_strcmp(tab[i], ".."))
			str = change_dr(str);
		else if (ft_strcmp(tab[i], "."))
			str = new_dr(str, tab[i]);
		i++;
	}
	printf ("%s\n", str);
	st = str;
	if (chdir(str) != 0)
		printf("Minishell>$ cd: %s: No such file or directory\n", tab[0]);
	else
	{
		st = ft_strjoin("PWD=", st);
		printf ("%s\n", st);
		new_pwd(st, env);
	}
}
