/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:49:05 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/28 13:16:54 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	in(t_cmd *cmd)
{
	int	fd;

	fd = 0;
	cmd = cmd->next;
	if (cmd)
	{
		if (cmd->type == SPACE)
			cmd = cmd->next;
		if (cmd)
		{
			if (cmd->type == SPACE)
				cmd = cmd->next;
			if (cmd)
				fd = open(cmd->str, O_RDWR);
		}
	}
	if (fd < 0)
		printf("%s : no such file or directory\n", cmd->str);
	return (fd);
}

int	out(t_cmd *cmd)
{
	int	fd;

	fd = 0;
	cmd = cmd->next;
	if (cmd)
	{
		if (cmd->type == SPACE)
			cmd = cmd->next;
		if (cmd)
		{
			if (cmd->type == SPACE)
				cmd = cmd->next;
			if (cmd)
				fd = open(cmd->str, O_CREAT | O_RDWR, 0777);
		}
	}
	if (fd < 0)
		printf("%s : no such file or directory\n", cmd->str);
	return (fd);
}

int	append(t_cmd *cmd)
{
	int	fd;

	fd = 0;
	cmd = cmd->next;
	if (cmd)
	{
		if (cmd->type == SPACE)
			cmd = cmd->next;
		if (cmd)
		{
			if (cmd->type == SPACE)
				cmd = cmd->next;
			if (cmd)
				fd = open(cmd->str, O_CREAT | O_APPEND | O_RDWR, 0777);
		}
	}
	if (fd < 0)
		printf("%s : no such file or directory\n", cmd->str);
	return (fd);
}

int	drop_util(int *i, t_var *p, int(*redire)(t_cmd *))
{
	(*i)--;
	p->fd_in = redire(p->tmp);
	if (p->fd_out < 0)
		return (1);
	if(*i)
		close(p->fd_in);
	return (0);
}

int	drop(t_var *p)
{
	if (p->tmp->type == IN)
	{
		if (drop_util(&p->l, p, in))
			return (1);
	}
	else if (p->tmp->type == OUT)
	{
		if (drop_util(&p->i, p, out))
			return (1);
	}
	else if (p->tmp->type == APPEND)
	{
		if (drop_util(&p->i, p, append))
			return (1);
	}
	if (p->lst && !p->l)
		p->lst->in = p->fd_in;
	if (p->lst && !p->i)
		p->lst->out = p->fd_out;
	p->tmp = p->tmp->next;
	return (0);
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
	p.l = count_fds(cmd, IN, 0);
	p.i = count_fds(cmd, OUT, 1);
	p.res = NULL;
	p.tmp = cmd;
	p.lst = *list;
	while (p.tmp)
	{
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
