/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:26:18 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/23 14:54:51 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *join_args(t_cmd **cmd)
{
    char *res;

    res = ft_strdup("");
    
    while ((*cmd) && (*cmd)->type != PIPE)
    {
        res = ft_strjoin(res, (*cmd)->str);
        (*cmd) = (*cmd)->next;
    }
    return (res);
}

int parser(t_cmd *cmd, t_list *list)
{
    t_var p;
    t_list *res;

    p.tmp = cmd;
    res = NULL;
    while (cmd)
    {
        p.s = join_args(&cmd);
        p.str = ft_split(p.s, ' ');
        if (!p.str || !p.str[0])
            return (1);
        list->cmd = p.str[0];
        list->args = p.str;
        if (cmd)
            cmd = cmd->next;
        if (list)
            list = list->next;
    }
    return(0);
}
