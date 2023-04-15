/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:41:06 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/10 17:45:09 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*del_redires(t_cmd *cmd)
{
	t_var	p;

	p.tmp = cmd;
	p.res = NULL;
	while (p.tmp)
	{
		if (p.tmp->type == OUT || p.tmp->type == IN || p.tmp->type == APPEND)
		{
			p.tmp = p.tmp->next;
			if (p.tmp)
			{
				if (p.tmp->type == SPACE)
					p.tmp = p.tmp->next;
				if (p.tmp)
					if (p.tmp->type == WORD || p.tmp->type == VAR)
						p.tmp = p.tmp->next;
			}
		}
		del_util(&p);
	}
	return (list_free(&cmd, ft_lstsize(cmd)), p.res);
}

t_cmd	*all(t_cmd *cmd, t_list **list)
{
	t_var	p;

	if (!cmd)
		return (NULL);
	p.j = 0;
	p.res = NULL;
	p.tmp = cmd;
	p.lst = *list;
	while (p.tmp)
	{
		p.l = count_fds(p.tmp, IN, 0);
		p.i = count_fds(p.tmp, OUT, 1);
		p.fd_in = 0;
		p.fd_out = 1;
		while (p.tmp && p.tmp->type != PIPE)
			if (drop(&p))
				return (NULL);
		p.lst = p.lst->next;
		if (p.tmp)
			p.tmp = p.tmp->next;
	}
	return (del_redires(cmd));
}

void	del_util(t_var *p)
{
	if (p->tmp && p->tmp->type != OUT && p->tmp->type != IN
		&& p->tmp->type != APPEND)
		ft_lstadd_back_cmd(&p->res, lst_new_cmd(p->tmp->str, p->tmp->type,
				p->tmp->quote));
	if (p->tmp && p->tmp->type != OUT && p->tmp->type != IN
		&& p->tmp->type != APPEND)
		p->tmp = p->tmp->next;
}

