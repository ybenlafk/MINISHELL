/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:29:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/18 15:54:53 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int    add_to_list(t_list **list, t_cmd *cmd, int stat)
{
    int fd;

    if (!stat)
        fd = open(cmd->next->next->str, O_CREAT | O_APPEND | O_RDWR, 0777);
    else
        fd = open(cmd->next->str, O_CREAT | O_APPEND | O_RDWR , 0777);
    close (fd);
    return (fd);
}

t_cmd	*redire_append(t_cmd *cmd, t_list **list)
{
	t_var p;
	t_cmd *res;

	if (!cmd)
		return (NULL);
	p.i = 0;
    p.l = 0;
	res = NULL;
	p.tmp = cmd;
	while (p.tmp)
	{
		is(&p, &p.tmp, APPEND);
		if (p.tmp->type == APPEND)
		{
			p.j = 1;
            p.fd = fill_list(&p, list, add_to_list);
            if (p.fd < 0)
                return (NULL);
		}
		else
		{
			ft_lstadd_back_cmd(&res, lst_new_cmd(p.tmp->str, p.tmp->type, p.tmp->quote, p.tmp->is_added));
			p.tmp = p.tmp->next;
		}
	}
	list_free(&cmd, ft_lstsize(cmd));
	return (res);
}
