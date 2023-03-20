/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:00:55 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/20 18:23:56 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int take_in(t_var *p, t_env *env , int stat)
{
    t_exp *exp;
    t_var var;

    exp = NULL;
    if (!stat)
        p->s1 = p->tmp->next->next->str;
    else
        p->s1 = p->tmp->next->str;
    p->fd = open(p->file, O_CREAT | O_RDWR | O_APPEND, 0777);
    if (p->fd < 0)
        return (1);
    while (1)
    {
        p->s = readline("heredoc> ");
        if (!p->s)
            return (1);
        if (!ft_strcmp(p->s, p->s1))
            break ;
        // lexer_pro_max(&exp, p->s, &var);
        // p->s = check_set(exp, env);
        p->s = char_join(p->s, '\n');
        write (p->fd, p->s, len(p->s) + 1);
        free(p->s);
        p->s = NULL;
    }
	p->tmp->str = "<";
	p->tmp->type = IN;
    if (!stat)
        p->tmp->next->next->str = p->file;
    else
        p->tmp->next->str = p->file;
    return (0);
}

t_cmd    *redire_heredoc(t_cmd *cmd, t_env *env, char *file)
{
    t_var p;
    t_cmd *res;

    p.file = file;
    if (!cmd)
		return (NULL);
    p.i = 0;
    res = NULL;
    p.tmp = cmd;
    while (p.tmp)
    {
        if (p.tmp->type == HEREDOC)
        {
            if (p.tmp->next->type == SPACE)
            {
                if(take_in(&p, env, 0))
                    return (NULL);
            }
            else
            {
                if(take_in(&p, env, 1))
                    return (NULL);
            }
        }
        ft_lstadd_back_cmd(&res, lst_new_cmd(p.tmp->str, p.tmp->type, p.tmp->quote, FALSE));
        p.tmp = p.tmp->next;
    }
    list_free(&cmd, ft_lstsize(cmd));
    return (res);
}
// 0ePOmn 