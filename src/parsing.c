/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:57:56 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/17 14:34:12 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lexer(t_cmd **list_cmd, char *s, t_var *p)
{
	p->i = 0;
	p->j = 0;
	p->l = 0;
	while (s[p->i])
	{
		p->s = NULL;
		if (sps_skiper(s, &p->i))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0));
		if (quotes_checker(list_cmd, s, p))
			return (list_free(list_cmd, ft_lstsize(*list_cmd)), 1);
		if (sps_skiper(s, &p->i))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0));
		redires_checker(list_cmd, s[p->i], s[p->i + 1], &p->i);
		if (sps_skiper(s, &p->i))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0));
		add_special_char(s[p->i], s[p->i + 1], list_cmd, p);
		if (sps_skiper(s, &p->i))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0));
		words_checker(p, list_cmd, s);
		vars_checker(p, list_cmd, s);
	}
	return (0);
}

int	parsing(t_cmd *cmd, char *output, t_env *env, t_list *list)
{
	t_var vars;
	t_list *tmp;
	char 	*syn;

	if (!output[0])
		return (0);
	vars.i = 0;
	(void)env;
	cmd = NULL;
	list = NULL;
	if (lexer(&cmd, output, &vars))
		return (1);
	syn = syntax_checker(cmd, output);
	if (syn)
		return (error(syn), 1);
	expanding(env, cmd);
	cmd = redire_heredoc(cmd, &list);
	cmd = redire_in(cmd, &list);
	cmd = redire_out(cmd, &list);
	cmd = redire_append(cmd, &list);
	cmd = two_to_one(cmd);
	while (cmd)
	{
		printf("|%s|\n", cmd->str);
		cmd = cmd->next;
	}
	printf("=================================\n");
	while (list)
	{
		printf("|%s|\n", list->cmd);
		printf("|%p|\n", list->args);
		printf("|%d|\n", list->in);
		printf("|%d|\n", list->out);
		list = list->next;
	}
	list_free(&cmd, ft_lstsize(cmd));
	return (0);
}
