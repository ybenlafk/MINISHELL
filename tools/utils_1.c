/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/05/07 12:03:34 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_parser(t_list **list)
{
	t_var	p;

	p.lst = *list;
	while (p.lst)
	{
		p.i = 0;
		if (p.lst->cmd && !p.lst->is)
		{
			if (!ft_strcmp(p.lst->cmd, "env"))
			{
				if (p.lst->args[1])
				{
					printf("env has no options : %s\n", p.lst->args[1]);
					free(p.lst->cmd);
					p.lst->cmd = NULL;
					free_all(p.lst->args);
					p.lst->args = NULL;
					p.i = 1;
				}
			}
		}
		p.lst = p.lst->next;
	}
	if (p.i)
		g_var.is = p.i;
}

t_cmd	*out_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*res;

	res = NULL;
	if (!cmd)
		return (NULL);
	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == OUT)
		{
			ft_lstadd_back_cmd(&res, lst_new_cmd(tmp->str, tmp->type,
					tmp->quote, tmp->is));
			if (tmp && tmp->next)
				if (tmp->next->type == PIPE)
					tmp = tmp->next;
		}
		else
			ft_lstadd_back_cmd(&res, lst_new_cmd(tmp->str, tmp->type,
					tmp->quote, tmp->is));
		tmp = tmp->next;
	}
	return (list_free(&cmd, ft_lstsize(cmd)), res);
}

t_cmd	*del_err(t_cmd *pev, t_cmd *cmd, int i)
{
	t_cmd	*tmp;
	t_cmd	*tmp1;
	t_cmd	*res;

	tmp = cmd;
	tmp1 = pev;
	res = NULL;
	while (tmp1 && i--)
	{
		ft_lstadd_back_cmd(&res, lst_new_cmd(tmp1->str, tmp1->type,
				tmp1->quote, tmp1->is));
		tmp1 = tmp1->next;
	}
	while (tmp)
	{
		ft_lstadd_back_cmd(&res, lst_new_cmd(tmp->str, tmp->type,
				tmp->quote, tmp->is));
		tmp = tmp->next;
	}
	return (res);
}

int	count_el(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	**duplicate(char **list)
{
	t_var	p;

	if (!list)
		return (NULL);
	p.str = malloc(count_el(list) * sizeof(char *) + 1);
	if (!p.str)
		return (NULL);
	p.i = 0;
	while (p.i < count_el(list))
	{
		p.str[p.i] = ft_strdup(list[p.i]);
		if (!p.str[p.i])
			return (free_all(p.str), NULL);
		p.i++;
	}
	p.str[p.i] = NULL;
	return (p.str);
}
