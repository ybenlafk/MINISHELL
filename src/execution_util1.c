/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:47:41 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/26 11:26:55 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_envcmp(char	*str)
{
	char	*st;
	int		i;

	i = 0;
	st = ft_strdup("PATH");
	while (i < 4)
	{
		if (st[i] != str[i])
			return (free(st), 0);
		i++;
	}
	return (free(st), 1);
}

char	**path_research(t_env	**env)
{
	t_env	*t;
	int		i;

	i = 0;
	t = *env;
	while (t)
	{
		if (ft_envcmp(t->e))
			return (ft_split(t->e + 5, ':'));
		t = t->next;
	}
	return (NULL);
}
