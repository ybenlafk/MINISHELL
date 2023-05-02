/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:47:41 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/02 21:52:40 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_envcmp(char	*str)
{
	char	*st;
	int		i;

	i = 0;
	st = "PATH";
	while (i < 4)
	{
		if (st[i] != str[i])
			return (0);
		i++;
	}
	return (1);
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
