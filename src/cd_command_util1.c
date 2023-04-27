/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_util1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:25:29 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/20 01:25:30 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*new_pwd_norm(t_env **env, char	*str)
{
	t_env	*t;

	t = *env;
	while (t)
	{
		if (ft_strncmp("PWD=", t->e, 4) == 0)
		{
			if (!ft_strcmp("PWD=/", t->e) && !ft_strcmp("PWD=/", str))
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
	char	*s2;
	char	*s1;

	t = *env;
	s1 = del_slash(str);
	if (check_pwd(env, "PWD"))
		s2 = new_pwd_norm(env, ft_strdup(s1));
	if (check_pwd(env, "OLDPWD"))
	{
		if (check_pwd(env, "PWD"))
			old_pwd(s2 + 4, env);
		else
			old_pwd("", env);
	}
	free(s1);
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

char	*env_oldpwd(t_env	**env)
{
	t_env			*t;

	t = *env;
	while (t)
	{
		if (!ft_strncmp("OLDPWD=", t->e, 7))
			return (t->e + 7);
		t = t->next;
	}
	return (NULL);
}
