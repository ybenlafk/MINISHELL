/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:26:18 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/24 14:48:56 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	freedom(char **p)
{
    int i;

    i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

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
        // p.str = ft_split(p.s, '~');
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
