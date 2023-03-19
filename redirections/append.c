/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:29:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/19 11:09:45 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int    add_to_list(t_cmd *cmd, int stat)
{
    int fd;

    if (!stat)
        fd = open(cmd->next->next->str, O_CREAT | O_APPEND | O_RDWR, 0777);
    else
        fd = open(cmd->next->str, O_CREAT | O_APPEND | O_RDWR , 0777);
    return (fd);
}

static int	drop(t_var *p, t_cmd **res, int *fd)
{
	is(p, &p->tmp, APPEND);
	if (p->tmp->type == PIPE)
    {
        if (!p->tmp->next)
            return (-1);
        p->l = set(&p->tmp->next, APPEND);
    }
	if (p->tmp->type == APPEND)
	{
		p->j = 1;
        *fd = fill_list(p, add_to_list);
        if (*fd < 0)
            return (1);
	}
	else
	{
		ft_lstadd_back_cmd(res, lst_new_cmd(p->tmp->str, p->tmp->type, p->tmp->quote, p->tmp->is_added));
		p->tmp = p->tmp->next;
	}
	return (0);
}

t_cmd	*redire_append(t_cmd *cmd, t_list **list, int *fd)
{
	t_var p;
	t_cmd *res;

	if (!cmd)
		return (NULL);
	p.j = 0;
	res = NULL;
	p.tmp = cmd;
	p.l = set(&p.tmp, APPEND);
	while (p.tmp)
	{
		p.i = drop(&p, &res, fd);
		if (p.i == -1)
			break;
		else if (p.i)
			return (NULL);
		if(p.j && p.l != -1)
        {
            ft_lstadd_back_list(list, lst_new_list(NULL, NULL, 0, *fd));
            p.j = 0;
        }
	}
	list_free(&cmd, ft_lstsize(cmd));
	return (res);
}
