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

int	drop_util(int *i, t_var *p, int(*redire)(t_cmd *), int stat)
{
	(*i)--;
	if (stat)
	{
		p->fd_in = redire(p->tmp);
		if (p->fd_in < 0)
			return (1);
	}
	else
	{
		p->fd_out = redire(p->tmp);
		if (p->fd_out < 0)
			return (1);
	}
	if (*i)
		close(p->fd_in);
	return (0);
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
	p->tmp = p->tmp->next;
	return (0);
}
