/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:57:56 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/28 20:33:01 by ybenlafk         ###   ########.fr       */
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

t_list	*parsing(t_cmd *cmd, t_var p, t_env *env)
{
	t_var	vars;
	t_list	*list;
	char	*syn;

	vars.i = 0;
	(void)env;
	cmd = NULL;
	list = NULL;
	if (lexer(&cmd, p.s, &vars))
		return (NULL);
	syn = syntax_checker(cmd, p.s);
	if (syn)
		return (list_free(&cmd, ft_lstsize(cmd)), error(syn), NULL);
	cmd = expanding(env, cmd);
	quotes_expander(cmd, env);
	cmd = lst_join(cmd);
	list = create_list(cmd);
	cmd = redire_heredoc(cmd, env);
	cmd = all(cmd, &list);
	cmd = two_to_one(cmd);
	if (export_parser(cmd))
		return(NULL);
	parser(cmd, list);
	list = unused_clear(list);
	// printf("<-------------------tokens-list---------------------->\n");
	// vars.tmp = cmd;
	// while (vars.tmp)
	// {
	// 	printf("value : |%s|\n", vars.tmp->str);
	// 	// printf("type : |%d|\n", vars.tmp->type);
	// 	// printf("quotes : |%d|\n", vars.tmp->quote);
	// 	vars.tmp = vars.tmp->next;
	// }
	// printf("<-------------------cmds-list------------------------>\n");
	// while (list)
	// {
	// 	int i = 0;
	// 	printf("cmd : |%s|\n", list->cmd);
	// 	if (list->args)
	// 		while (list->args[i])
	// 			printf("arg : {%s}\n", list->args[i++]);
	// 	printf("in : |%d|\n", list->in);
	// 	printf("out : |%d|\n", list->out);
	// 	printf("<<<<<<----------------->>>>>>\n");
	// 	list = list->next;
	// }
	list_free(&cmd, ft_lstsize(cmd));
	return (list);
}
