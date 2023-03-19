/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:26:18 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/19 15:36:54 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *f(t_cmd *cmd)
{
    t_cmd *s;
    char *res;

    res = ft_strdup("");
    s = cmd;
    
    while (s && s->type != PIPE)
    {
        res = ft_strjoin(res, s->str);
        s = s->next;
    }
    return (res);
}

t_list    *parser(t_cmd *cmd, t_list **list)
{
    t_list *res;
    t_cmd *tmp;

    res = *list;
    tmp = cmd;
    while (cmd && cmd->is_added == FALSE)
        cmd = cmd->next;
    res->cmd = ft_split(f(cmd), ' ')[0];
    res->args = ft_split(f(cmd), ' ');
    res = res->next;
    while (tmp)
    {
        if (tmp->type == PIPE)
        {
            while (cmd && cmd->is_added == FALSE)
                cmd = cmd->next;
            tmp = tmp->next;
            res->cmd = ft_split(f(tmp), ' ')[0];
            res->args = ft_split(f(tmp), ' ');
            res = res->next;
        }
        tmp = tmp->next;
    }
    return (*list);
}