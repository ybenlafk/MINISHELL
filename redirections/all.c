/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:49:05 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/21 22:00:06 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    in(t_cmd *cmd, int stat)
{
    int fd;
    char *s = ft_strdup("");
    
    if (!stat)
    {
        s = ft_strjoin(s, cmd->next->next->str);
        fd = open(s, O_RDWR);
    }
    else
    {
        s = ft_strjoin(s, cmd->next->str);
        fd = open(s, O_RDWR);
    }
    return (fd);
}

int    out(t_cmd *cmd, int stat)
{
    int fd;
    char *s = ft_strdup("../lx/");
    
    if (!stat)
    {
        s = ft_strjoin(s, cmd->next->next->str);
        fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0777);
    }
    else
    {
        s = ft_strjoin(s, cmd->next->str);
        fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0777);
    }
    return (fd);
}

int    append(t_cmd *cmd, int stat)
{
    int fd;
    char *s = ft_strdup("");
    
    if (!stat)
    {
        s = ft_strjoin(s, cmd->next->next->str);
        fd = open(s, O_CREAT | O_APPEND | O_RDWR, 0777);
    }
    else
    {
        s = ft_strjoin(s, cmd->next->str);
        fd = open(s, O_CREAT | O_APPEND | O_RDWR, 0777);
    }
    return (fd);
}

static int	drop(t_var *p, t_cmd **res, int *fd)
{
	is(p, &p->tmp);
    if (p->tmp->type == PIPE)
    {
        if (!p->tmp->next)
            return (-1);
        p->l = set(&p->tmp->next);
    }
    if (p->tmp->type == OUT)
    {
        p->j = OUT;
        *fd = fill_list(p, out);
        if (*fd < 0)
            return (1);
    }
    else if (p->tmp->type == IN)
    {
        p->j = IN;
        *fd = fill_list(p, in);
        if (*fd < 0)
            return (1);
    }
    else if (p->tmp->type == APPEND)
    {
        p->j = APPEND;
        *fd = fill_list(p, append);
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

t_cmd    *all(t_cmd *cmd, t_list **list, int *fd)
{
    t_var p;
    t_cmd *res;

    if (!cmd)
		return (NULL);
    p.j = 0;
    res = NULL;
    p.tmp = cmd;
    p.l = set(&p.tmp);
    while (p.tmp)
    {
        p.i = drop(&p, &res, fd);
		if (p.i == -1)
			break;
		else if (p.i)
			return (NULL);
        if(p.j == OUT)
        {
            ft_lstadd_back_list(list, lst_new_list(NULL, NULL, 0, *fd));
            p.j = 0;
        }
        else if(p.j == IN)
        {
            ft_lstadd_back_list(list, lst_new_list(NULL, NULL, *fd, 1));
            p.j = 0;
        }
        else if(p.j == APPEND)
        {
            ft_lstadd_back_list(list, lst_new_list(NULL, NULL, 0, *fd));
            p.j = 0;
        }
    }
    list_free(&cmd, ft_lstsize(cmd));
    return (res);
}
