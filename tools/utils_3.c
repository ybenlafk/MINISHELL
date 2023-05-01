/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/05/01 13:06:19 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*create_list(t_cmd *cmd)
{
	t_var	p;
	t_list	*res;

	res = NULL;
	p.i = pipe_count(cmd);
	p.i++;
	while (p.i--)
		ft_lstadd_back_list(&res, lst_new_list(NULL, NULL, 0, 1));
	return (res);
}

void	add_new(t_var *p, t_cmd **res)
{
	while (p->tmp)
	{
		if (p->tmp->type == SPACE && p->tmp->next)
		{
			if (p->tmp->next->type == SPACE)
				p->tmp = p->tmp->next;
			else
			{
				ft_lstadd_back_cmd(res, lst_new_cmd(p->tmp->str, p->tmp->type,
						p->tmp->quote));
				p->tmp = p->tmp->next;
			}
		}
		else
		{
			ft_lstadd_back_cmd(res, lst_new_cmd(p->tmp->str, p->tmp->type,
					p->tmp->quote));
			p->tmp = p->tmp->next;
		}
	}
}

t_cmd	*two_to_one(t_cmd *cmd)
{
	t_var	p;
	t_cmd	*res;

	if (!cmd)
		return (NULL);
	p.tmp = cmd;
	res = NULL;
	add_new(&p, &res);
	list_free(&cmd, ft_lstsize(cmd));
	return (res);
}

int	count_fds(t_cmd *cmd, int type, int stat)
{
	t_var	p;

	p.i = 0;
	p.tmp = cmd;
	while (p.tmp && p.tmp->type != PIPE)
	{
		if (!stat)
		{
			if (p.tmp->type == type)
				p.i++;
		}
		else if (p.tmp->type == type || p.tmp->type == APPEND)
			p.i++;
		p.tmp = p.tmp->next;
	}
	return (p.i);
}

t_cmd	*del_cmd(t_cmd **lst, char *str)
{
	t_cmd	*t;
	t_cmd	*tmp;

	tmp = *lst;
	t = NULL;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->str) != 0)
			ft_lstadd_back_cmd(&t, lst_new_cmd(tmp->str, tmp->type,
					tmp->quote));
		tmp = tmp->next;
	}
	return (t);
}
