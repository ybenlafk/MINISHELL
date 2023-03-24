/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:49:05 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/24 14:17:25 by ybenlafk         ###   ########.fr       */
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
			printf(">>%s\n", cmd->str);
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
			printf(">>%s\n", cmd->str);
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
			printf(">>%s\n", cmd->str);
			if (cmd)
				fd = open(cmd->str, O_CREAT | O_APPEND | O_RDWR, 0777);
		}
	}
	if (fd < 0)
		printf("%s : no such file or directory\n", cmd->str);
	return (fd);
}

int	drop(t_var *p)
{
	if (p->tmp->type == IN)
	{
		p->fd_in = in(p->tmp);
		if (p->fd_out < 0)
			return (1);
	}
	else if (p->tmp->type == OUT)
	{
		p->fd_out = out(p->tmp);
		if (p->fd_out < 0)
			return (1);
	}
	else if (p->tmp->type == APPEND)
	{
		p->fd_out = append(p->tmp);
		if (p->fd_out < 0)
			return (1);
	}
	p->tmp = p->tmp->next;
	if (p->lst)
	{
		p->lst->in = p->fd_in;
		p->lst->out = p->fd_out;
	}
	return (0);
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
		if (p.tmp && p.tmp->type != OUT && p.tmp->type != IN
			&& p.tmp->type != APPEND)
			ft_lstadd_back_cmd(&p.res, lst_new_cmd(p.tmp->str, p.tmp->type,
					p.tmp->quote));
		if (p.tmp && p.tmp->type != OUT && p.tmp->type != IN
			&& p.tmp->type != APPEND)
			p.tmp = p.tmp->next;
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
	p.fd_in = 0;
	p.fd_out = 1;
	p.tmp = cmd;
	p.lst = *list;
	while (p.tmp)
	{
		while (p.tmp && p.tmp->type != PIPE)
			if (drop(&p))
				return (NULL);
		p.lst = p.lst->next;
		if (p.tmp)
			p.tmp = p.tmp->next;
	}
	return (del_redires(cmd));
}
