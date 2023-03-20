/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:26:18 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/20 19:05:36 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *join_args(t_cmd *cmd)
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

t_list    *parser(t_cmd *cmd, t_list *list)
{
    t_list *res;
    t_cmd *tmp;
    char    **s;

    res = NULL;
    tmp = cmd;
    while (tmp && (tmp->type != WORD && tmp->type != VAR))
        tmp = tmp->next;
    if (!tmp)
        return (list);
    s = ft_split(join_args(tmp), ' ');
    if (!s)
        return (NULL);
    if (tmp->is_added)
    {
        ft_lstadd_back_list(&res, lst_new_list(s[0], s, list->in, list->out));
        list = list->next;
    }
    else
        ft_lstadd_back_list(&res, lst_new_list(s[0], s, 0, 1));
    while (tmp)
    {
        if (tmp->type == PIPE)
        {
            while (tmp && (tmp->type != WORD && tmp->type != VAR))
                tmp = tmp->next;
            if (!tmp)
                return (list);
            s = ft_split(join_args(tmp), ' ');
            if (tmp->is_added)
            {
                ft_lstadd_back_list(&res, lst_new_list(s[0], s, list->in, list->out));
                list = list->next;
            }
             else
                ft_lstadd_back_list(&res, lst_new_list(s[0], s, 0, 1));
        }
        tmp = tmp->next;
    }
    return (res);
}