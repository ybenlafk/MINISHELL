/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:00:55 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 17:46:52 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctl_c()
{
	close(0);
}

int	take_in(t_var *p, t_env *env, int stat)
{
	t_exp	*exp;
	t_var	var;
	t_var	l;
	t_cmd	*use;

	if (!stat)
		use = p->tmp->next->next;
	else
		use = p->tmp->next;
	p->fd = open(p->file, O_CREAT | O_RDWR | O_APPEND | O_TRUNC, 0777);
	if (p->fd < 0)
		return (p->fd);
	while (1)
	{
		exp = NULL;
		signal(SIGINT, ctl_c);
		p->s = readline("heredoc> ");
		if (!p->s)
			break ;
		if (!ft_strcmp(p->s, use->str))
		{
			free(p->s);
			break ;
		}
		if (!use->quote)
		{
			lexer_pro_max(&exp, p->s, &var);
			free(p->s);
			p->s = check_set(exp, env);
			free_exp(&exp, ft_lstsize_exp(exp));
		}
		p->s = char_join(p->s, '\n');
		write (p->fd, p->s, len(p->s) + 1);
		free(p->s);
	}
	free(p->tmp->str);
	p->tmp->str = ft_strdup("<");
	p->tmp->type = IN;
	free(use->str);
	if (!ttyname(0))
	{
		l.s = ttyname(2);
		l.fd = open(l.s, O_RDONLY);
		dup2(l.fd, 0);
		// p->fd = 0;
	}
	use->str = ft_strdup(p->file);
	return (p->fd);
}

t_cmd	*redire_heredoc(t_cmd *cmd, t_env *env)
{
	t_var	p;
	t_cmd	*res;

	if (!cmd)
		return (NULL);
	p.i = 0;
	res = NULL;
	p.tmp = cmd;
	while (p.tmp)
	{
		if (p.tmp->type == HEREDOC)
		{
			p.file = generate_name();
			if (p.tmp->next->type == SPACE)
			{
				p.fd = take_in(&p, env, 0);
				if (p.fd < 0)
					return (NULL);
			}
			else
			{
				p.fd = take_in(&p, env, 1);
				if (p.fd < 0)
					return (NULL);
			}
			free(p.file);
			close(p.fd);
		}
		ft_lstadd_back_cmd(&res,
			lst_new_cmd(p.tmp->str, p.tmp->type, p.tmp->quote));
		p.tmp = p.tmp->next;
	}
	list_free(&cmd, ft_lstsize(cmd));
	return (res);
}
