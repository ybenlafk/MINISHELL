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

void	del_util(t_var *p)
{
	if (p->tmp && p->tmp->type != OUT && p->tmp->type != IN
		&& p->tmp->type != APPEND)
		ft_lstadd_back_cmd(&p->res, lst_new_cmd(p->tmp->str, p->tmp->type,
				p->tmp->quote, p->tmp->is));
	if (p->tmp && p->tmp->type != OUT && p->tmp->type != IN
		&& p->tmp->type != APPEND)
		p->tmp = p->tmp->next;
}

t_cmd	*del_redires(t_cmd *cmd)
{
	t_var	p;

	p.tmp = cmd;
	p.res = NULL;
	if (!cmd)
		return (NULL);
	while (p.tmp)
	{
		if (p.tmp->type == OUT || p.tmp->type == IN || p.tmp->type == APPEND)
		{
			p.tmp = p.tmp->next;
			if (p.tmp && p.tmp->type == SPACE)
				p.tmp = p.tmp->next;
			if (p.tmp && (p.tmp->type == WORD || p.tmp->type == VAR))
				p.tmp = p.tmp->next;
		}
		del_util(&p);
	}
	return (list_free(&cmd, ft_lstsize(cmd)), p.res);
}

int	drop_util(int *i, t_var *p, int (*redire)(t_cmd *), int stat)
{
	(*i)--;
	if (stat)
	{
		p->fd_in = redire(p->tmp);
		if (p->fd_in == -1)
			return (1);
		if (*i)
			close(p->fd_in);
	}
	else
	{
		p->fd_out = redire(p->tmp);
		if (p->fd_out == -1)
			return (1);
		if (*i)
			close(p->fd_out);
	}
	return (0);
}

void	fds_init(t_var *p)
{
	p->l = count_fds(p->tmp, IN, 0);
	p->i = count_fds(p->tmp, OUT, 1);
	p->fd_in = 0;
	p->fd_out = 1;
}
