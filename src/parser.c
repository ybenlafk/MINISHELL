/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:26:18 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/04 19:34:56 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int lst_len(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd && cmd->type != PIPE)
    {
        if (cmd->type != SPACE)
            i++;
        cmd = cmd->next;
    }
    return (i);
}

char **join_args(t_cmd **cmd)
{
    t_var p;
    char **res;

    p.i = 0;
    res = (char **)malloc((lst_len(*cmd) + 1) * sizeof(char *));;
    if (!res)
        return (NULL);
    while ((*cmd) && (*cmd)->type != PIPE)
    {
        if ((*cmd)->type != SPACE)
            res[p.i++] = ft_strdup((*cmd)->str);
        (*cmd) = (*cmd)->next;
    }
    res[p.i] = NULL;
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
        p.str = join_args(&cmd);
        if (!p.str)
            return (1);
        list->cmd = ft_strdup(p.str[0]);
        list->args = p.str;
        if (cmd)
            cmd = cmd->next;
        if (list)
            list = list->next;
    }
    // freedom(p.str);
    return(0);
}
