/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 00:32:42 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/21 16:23:28 by nouahidi         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (1)
	{
		if (!str[0])
			return (0);
		if (chdir(str) != -1)
			return (free(str), 1);
		else
			str = del_dr(str);
	}
	return (0);
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
