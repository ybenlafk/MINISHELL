/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:57:56 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/19 16:32:30 by ybenlafk         ###   ########.fr       */
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
	while (tmp)
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
		while (i--)
			p = p->next;
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	return (res);
}

int	parsing(t_cmd *cmd, char *output, t_env *env, t_list *list)
{
	t_var vars;
	t_cmd *tmp;
	char 	*syn;

	if (!output[0])
		return (0);
	vars.i = 0;
	int fd = -1;
	(void)env;
	cmd = NULL;
	list = NULL;
	if (lexer(&cmd, output, &vars))
		return (1);
	expanding(env, cmd);
	syn = syntax_checker(cmd, output);
	if (syn)
		return (error(syn), 1);
	tmp = lst_dup(cmd);
	cmd = redire_heredoc(cmd);
	cmd = all(cmd, &list, &fd);
	cmd = two_to_one(cmd);
	list = fin(&list, tmp);
	list = parser(cmd, &list);
	while (cmd)
	{
		printf("|%s|\n", cmd->str);
		printf("|%d|\n", cmd->is_added);
		cmd = cmd->next;
	}
	printf("=================================\n");
	// while (list)
	// {
	// 	int i = 0;
	// 	printf("|%s|\n", list->cmd);
	// 	while (list->args[i])
	// 		printf("{%s}\n", list->args[i++]);
	// 	printf("|%d|\n", list->in);
	// 	printf("|%d|\n", list->out);
	// 	list = list->next;
	// }
	list_free(&cmd, ft_lstsize(cmd));
	close(fd);
	return (0);
}
