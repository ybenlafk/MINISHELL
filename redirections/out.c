/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:19:39 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/18 18:33:52 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int    add_to_list(t_list **list, t_cmd *cmd, int stat)
{
    int fd;

    if (!stat)
        fd = open(cmd->next->next->str, O_CREAT | O_RDWR | O_TRUNC, 0777);
    else
        fd = open(cmd->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    return (fd);
}

t_cmd    *redire_out(t_cmd *cmd, t_list **list, int *fd)
{
    t_var p;
    t_cmd *res;

    if (!cmd)
		return (NULL);
    p.i = 0;
    p.j = 0;
    p.l = 0;
    res = NULL;
    p.tmp = cmd;
    while (p.tmp)
    {
        is(&p, &p.tmp, OUT);
        if (p.tmp->type == OUT)
        {
            p.j = 1;
            *fd = fill_list(&p, list, add_to_list);
            if (*fd < 0)
                return (NULL);
        }
        else
        {
            ft_lstadd_back_cmd(&res, lst_new_cmd(p.tmp->str, p.tmp->type, p.tmp->quote, p.tmp->is_added));
            p.tmp = p.tmp->next;
        }
    }
    if(p.j)
        ft_lstadd_back_list(list, lst_new_list(NULL, NULL, 0, *fd));
    list_free(&cmd, ft_lstsize(cmd));
    return (res);
}
