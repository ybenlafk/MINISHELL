/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:26:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/21 20:27:14 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int redire_checker(t_cmd **cmd, int type)
{
    if ((*cmd)->type == type && !(*cmd)->next)
        return (1);
    if ((*cmd)->type == type && (*cmd)->next->type == SPACE)
    {
        if (!(*cmd)->next->next)
            return (1);
        if ((*cmd)->next->next->type != WORD && (*cmd)->next->next->type != VAR)
            return (1);
    }
    else if ((*cmd)->type == type && (*cmd)->next->type != WORD && (*cmd)->next->type != VAR)
        return (1);
    return (0);
}

int is_doubl_pipe(t_cmd *cmd)
{
    t_cmd *tmp;

    tmp = cmd;
    while (tmp)
    {
        if (tmp->type == PIPE)
        {
            if (tmp->next->type == PIPE)
                return (1);
            else if (tmp->next->type == SPACE && tmp->next->next->type == PIPE)
                return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

int pipe_checker(t_cmd *cmd)
{
    t_var p;

    p.tmp = cmd;
    if (!cmd)
        return (0);
    if (p.tmp->type == PIPE)
        if (!p.tmp->next)
            return (1);
    if (p.tmp->next)
    {
        if (p.tmp->type == PIPE || (p.tmp->type == SPACE && p.tmp->next->type == PIPE))
            return (1);
    }
    if (!p.tmp->next)
        return (0);
    while (p.tmp->next->next)
        p.tmp = p.tmp->next;
    if (p.tmp->next->type == PIPE || (p.tmp->next->type == SPACE && p.tmp->type == PIPE))
        return (1);
    if (is_doubl_pipe(cmd))
        return (1);
    return (0);
}

char    *syntax_checker(t_cmd *cmd, char *str)
{
    t_var p;

    p.tmp = cmd;
    if (pipe_checker(p.tmp))
        return ("|");
    if (check_or(str, '|'))
		return ("||");
	if (check_or(str, '&'))
		return ("&&");
    while (p.tmp)
    {
        if (redire_checker(&p.tmp, IN))
            return ("<");
        if (redire_checker(&p.tmp, OUT))
            return (">");
        if (redire_checker(&p.tmp, HEREDOC))
            return ("<<");
        if (redire_checker(&p.tmp, APPEND))
            return (">>");
        p.tmp = p.tmp->next;
    }
    return (NULL);
}