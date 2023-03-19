/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:00:51 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/19 10:53:40 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int    add_to_list(t_cmd *cmd, int stat)
{
    int fd;

    if (!stat)
        fd = open(cmd->next->next->str, O_RDWR);
    else
        fd = open(cmd->next->str, O_WRONLY);
    return (fd);
}

static int	drop(t_var *p, t_cmd **res, int *fd)
{
	is(p, &p->tmp, IN);
    if (p->tmp->type == PIPE)
    {
        if (!p->tmp->next)
            return (-1);
        p->l = set(&p->tmp->next, IN);
    }
    if (p->tmp->type == IN)
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

t_cmd    *redire_in(t_cmd *cmd, t_list **list, int *fd)
{
    t_var p;
    t_cmd *res;

    if (!cmd)
		return (NULL);
    p.j = 0;
    res = NULL;
    p.tmp = cmd;
    p.l = set(&p.tmp, IN);
    while (p.tmp)
    {
        p.i = drop(&p, &res, fd);
		if (p.i == -1)
			break;
		else if (p.i)
			return (NULL);
        if(p.j && p.l != -1)
        {
            ft_lstadd_back_list(list, lst_new_list(NULL, NULL, *fd, 1));
            p.j = 0;
        }
    }
    list_free(&cmd, ft_lstsize(cmd));
    return (res);
}
