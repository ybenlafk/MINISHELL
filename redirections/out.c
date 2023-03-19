/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:19:39 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/19 11:10:06 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int    add_to_list(t_cmd *cmd, int stat)
{
    int fd;

    if (!stat)
        fd = open(cmd->next->next->str, O_CREAT | O_RDWR | O_TRUNC, 0777);
    else
        fd = open(cmd->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    return (fd);
}

static int	drop(t_var *p, t_cmd **res, int *fd)
{
	is(p, &p->tmp, OUT);
    if (p->tmp->type == PIPE)
    {
        if (!p->tmp->next)
            return (-1);
        p->l = set(&p->tmp->next, OUT);
    }
    if (p->tmp->type == OUT)
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

t_cmd    *redire_out(t_cmd *cmd, t_list **list, int *fd)
{
    t_var p;
    t_cmd *res;

    if (!cmd)
		return (NULL);
    p.j = 0;
    res = NULL;
    p.tmp = cmd;
    p.l = set(&p.tmp, OUT);
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
