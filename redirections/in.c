/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:00:51 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/17 14:25:50 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int    add_to_list(t_list **list, t_cmd *cmd, int stat)
{
    int fd;

    if (!stat)
    {
        fd = open(cmd->next->next->str, O_RDWR);
        if (fd < 0)
            return (1);
        ft_lstadd_back_list(list, lst_new_list(NULL, NULL, fd, 1));
    }
    else
    {
        fd = open(cmd->next->str, O_RDONLY);
        if (fd < 0)
            return (1);
        ft_lstadd_back_list(list, lst_new_list(NULL, NULL, fd, 1));
    }
    return (0);
}

t_cmd    *redire_in(t_cmd *cmd, t_list **list)
{
    t_var p;
    t_cmd *res;

    if (!cmd)
		return (NULL);
    p.i = 0;
    res = NULL;
    p.tmp = cmd;
    while (p.tmp)
    {
        if (p.tmp->type == IN)
        {
            if (fill_list(&p, list, add_to_list))
                return (NULL);
        }
        else
        {
            ft_lstadd_back_cmd(&res, lst_new_cmd(p.tmp->str, p.tmp->type, p.tmp->quote));
            p.tmp = p.tmp->next;
        }
    }
    list_free(&cmd, ft_lstsize(cmd));
    return (res);
}