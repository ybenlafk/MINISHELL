/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:24:06 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/09 12:45:29 by ybenlafk         ###   ########.fr       */
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

void	new_pwd(char *str, t_env **env)
{
	t_env	*t;

	t = *env;
	while (t)
	{
		if (ft_strncmp("PWD=", t->e, 3) == 0)
		{
			if (!ft_strcmp(ft_strjoin("PWD=", "/"), t->e) && !ft_strcmp(ft_strjoin("PWD=", "/"), str))
				break ;
			ft_lstadd_back(env, ft_lstnew(str));
			*env = ft_lstdelone(env, t->e);
			break ;
		}
		t = t->next;
	}
	old_pwd(t->e + 4, env);
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
	while (str[j] != '/')
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

void    cd_cmd(t_list   *lst, t_env **env)
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
	st = str;
	if(chdir(str) != 0)
		printf("Minishell>$ cd: %s: No such file or directory\n", tab[0]);
	st = ft_strjoin("PWD=", st);
	new_pwd(st, env);
}
