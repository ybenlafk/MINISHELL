/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/16 22:57:56 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 18:16:41 by nouahidi         ###   ########.fr       */
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
		if (redires_checker(list_cmd, s, &p->i))
			return (list_free(list_cmd, ft_lstsize(*list_cmd)), 1);
		if (sps_skiper(s, &p->i))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0));
		add_special_char(s, list_cmd, p);
		if (sps_skiper(s, &p->i))
			ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0));
		words_checker(p, list_cmd, s);
		vars_checker(p, list_cmd, s);
	}
	return (0);
}

void	parsing_norm(t_cmd **cmd, t_list **list, t_env *env)
{
	*list = create_list(*cmd);
	*cmd = redire_heredoc(*cmd, env);
	*cmd = all(*cmd, list);
	*cmd = two_to_one(*cmd);
	parser(*cmd, *list);
	export_parser(list);
	env_parser(list);
	*list = unused_clear(*list);
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
	cmd = expanding(env, cmd);
	quotes_expander(cmd, env);
	cmd = out_pipe(cmd);
	syn = syntax_checker(cmd);
	if (syn)
		return (list_free(&cmd, ft_lstsize(cmd)), error(syn), NULL);
	cmd = lst_join(cmd);
	if (pipe_count(cmd) >= 540)
		return (list_free(&cmd, ft_lstsize(cmd)),
			ft_putstr_fd("Minishell: fork: Resource temporarily unavailable\n",
				2), NULL);
	parsing_norm(&cmd, &list, env);
	list_free(&cmd, ft_lstsize(cmd));
	return (list);
}
