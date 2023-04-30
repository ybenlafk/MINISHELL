/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:41:33 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/30 17:19:13 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	srch_cmd(t_list *list)
{
	int	i;

	i = 0;
	if (!ft_strcmp(list->cmd, "cd"))
		return (1);
	if (!ft_strcmp(list->cmd, "export"))
		return (2);
	if (!ft_strcmp(list->cmd, "pwd"))
		return (3);
	if (!ft_strcmp(list->cmd, "echo"))
		return (4);
	if (!ft_strcmp(list->cmd, "unset"))
		return (5);
	if (!ft_strcmp(list->cmd, "env"))
		return (6);
	if (!ft_strcmp(list->cmd, "exit"))
		return (7);
	return (0);
}

int	lst_size_list(t_list *list)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	pipe_cases(t_var *var, t_var *p)
{
	if (var->j && !var->lst->next)
	{
		dup2(var->stat, 0);
		if (close(p->fds[1]) == -1 || close(p->fds[0]) == -1)
			exit(errno);
	}
	else
	{
		dup2(p->fds[1], 1);
		dup2(var->stat, 0);
		if (close(p->fds[1]) == -1 || close(p->fds[0]) == -1)
			exit(errno);
	}
}

char	*valid_path(char	**tab, char *str)
{
	int		i;
	char	*st;
	t_var 	p;

	i = 0;
	if (!tab[0])
		return (NULL);
	while (tab[i])
	{
		st = char_join(ft_strdup(tab[i]), '/');
		p.s = ft_strjoin(st, str);
		if (access(p.s, X_OK) == 0)
			return (tab[i]);
		i++;
	}
	return (free(p.s), NULL);
}

char	*ft_strchr(const char *str, int s)
{
	int		i;

	i = 0;
	while (str[i] != (char)s)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)str + i);
}
