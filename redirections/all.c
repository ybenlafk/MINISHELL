/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:49:05 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 17:45:03 by nouahidi         ###   ########.fr       */
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
	{
		gvar.g_exit_status = 1;
		printf("%s : no such file or directory\n", cmd->str);
	}
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
	{
		gvar.g_exit_status = 1;
		printf("%s : no such file or directory\n", cmd->str);
	}
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
	{
		gvar.g_exit_status = 1;
		printf("%s : no such file or directory\n", cmd->str);
	}
	return (fd);
}

int	drop(t_var *p)
{
	if (p->tmp->type == IN)
	{
		if (drop_util(&p->l, p, in, 1))
			return (1);
	}
	else if (p->tmp->type == OUT)
	{
		if (drop_util(&p->i, p, out, 0))
			return (1);
	}
	else if (p->tmp->type == APPEND)
	{
		if (drop_util(&p->i, p, append, 0))
			return (1);
	}
	if (p->lst && !p->l)
		p->lst->in = p->fd_in;
	if (p->lst && !p->i)
		p->lst->out = p->fd_out;
	return (0);
}

t_cmd	*all(t_cmd *cmd, t_list **list)
{
	t_var	p;
	t_cmd *res;

	if (!cmd)
		return (NULL);
	p.j = 0;
	p.is = 0;
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
		{
			if (drop(&p))
				p.lst->is = 1;
			p.tmp = p.tmp->next;
		}
		p.lst = p.lst->next;
		if (p.tmp)
			p.tmp = p.tmp->next;
	}
	return (del_redires(cmd));
}