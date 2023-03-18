/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:00:55 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/17 20:50:46 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int take_in(t_var *p)
{
    p->fd = open("/tmp/test", O_CREAT | O_RDWR | O_APPEND, 0777);
    if (p->fd < 0)
        return (1);
    while (1)
    {
        p->s = readline("heredoc> ");
        if (!p->s)
            return (1);
        if (!ft_strcmp(p->s, p->tmp->next->next->str))
            break ;
        write (p->fd, char_join(p->s, '\n'), len(p->s) + 1);
        free(p->s);
    }
	p->tmp->str = "<";
	p->tmp->type = IN;
    p->tmp->next->next->str = "/tmp/test";
    return (0);
}

t_cmd    *redire_heredoc(t_cmd *cmd, t_list **list)
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
        if (p.tmp->type == HEREDOC)
            if (p.tmp->next->type == SPACE)
                if(take_in(&p))
                    return (NULL);
        ft_lstadd_back_cmd(&res, lst_new_cmd(p.tmp->str, p.tmp->type, p.tmp->quote));
        p.tmp = p.tmp->next;
    }
    list_free(&cmd, ft_lstsize(cmd));
    return (res);
}
