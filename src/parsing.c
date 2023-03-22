/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:57:56 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/22 23:46:03 by ybenlafk         ###   ########.fr       */
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
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0, FALSE));
		if (quotes_checker(list_cmd, s, p))
			return (list_free(list_cmd, ft_lstsize(*list_cmd)), 1);
		if (sps_skiper(s, &p->i))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0, FALSE));
		redires_checker(list_cmd, s[p->i], s[p->i + 1], &p->i);
		if (sps_skiper(s, &p->i))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0, FALSE));
		add_special_char(s[p->i], s[p->i + 1], list_cmd, p);
		if (sps_skiper(s, &p->i))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0, FALSE));
		words_checker(p, list_cmd, s);
		vars_checker(p, list_cmd, s);
	}
	return (0);
}

t_list *fin(t_list **list, t_cmd *cmd)
{
	t_list *res;
	t_list *p;
	t_cmd *tmp;
	int i = 0;

	res = NULL;
	tmp = cmd;
	p = *list;
	while (tmp && p)
	{
		i = 0;
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == APPEND || tmp->type == IN
				|| tmp->type == OUT || tmp->type == HEREDOC)
				i++;
			tmp = tmp->next;
		}

		ft_lstadd_back_list(&res, lst_new_list(NULL, NULL, p->in, p->out));
		while (i-- && p)
			p = p->next;
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	return (res);
}

t_list	*parsing(t_cmd *cmd, t_var p, t_env *env)
{
	t_var	vars;
	t_list	*list;
	t_cmd 	*tmp;
	char 	*syn;

	if (!p.s[0])
		return (0);
	vars.i = 0;
	int fd = -1;
	(void)env;
	cmd = NULL;
	list = NULL;
	if (lexer(&cmd, p.s, &vars))
		return (NULL);
	expanding(env, cmd);
	cmd = lst_join(cmd);
	syn = syntax_checker(cmd, p.s);
	if (syn)
		return (error(syn), NULL);
	tmp = lst_dup(cmd);
	cmd = redire_heredoc(cmd, env, p.file);
	cmd = all(cmd, &list, &fd);
	cmd = two_to_one(cmd);
	list = fin(&list, tmp);
	list = parser(cmd, list);
	list = unused_clear(list);
	printf("<-------------------tokens-list---------------------->\n");
	while (cmd)
	{
		printf("value : |%s|\n", cmd->str);
		// printf("type : |%d|\n", cmd->type);
		// printf("quotes : |%d|\n", cmd->quote);
		printf("is added : |%d|\n", cmd->is_added);
		cmd = cmd->next;
	}
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
	close(fd);
	return (list);
}
