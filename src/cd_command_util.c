/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 00:32:42 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/30 16:58:48 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_home(t_env **env)
{
	t_env	*t;

	t = *env;
	while (t)
	{
		if (!ft_strncmp("HOME=", t->e, 5))
			return (t->e + 5);
		t = t->next;
	}
	return (NULL);
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
		if (str[i] == '/' || !i)
			break ;
		i--;
	}
	i--;
	st = malloc(i + 1);
	if (!st)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		st[j] = str[j];
		j++;
	}
	st[j] = '\0';
	return (free(str), st);
}

int	new_path(char	*str)
{
	int		i;
	char	*st;

	st = ft_strdup(str);
	i = 0;
	while (1)
	{
		if (!st[0])
			return (0);
		if (chdir(st) != -1)
			return (free(st), 1);
		else
			st = del_dr(st);
	}
	return (free(st), 0);
}

char	*get_pwd(t_env **env)
{
	t_env	*t;

	t = *env;
	while (t)
	{
		if (!ft_strncmp("PWD=", t->e, 4))
			return (t->e);
		t = t->next;
	}
	return (NULL);
}

int	del_head(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}
