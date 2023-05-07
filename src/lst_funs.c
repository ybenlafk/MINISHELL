/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 23:20:13 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/05/07 11:44:35 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*p;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			p = ft_lstlast_env(*lst);
			p->next = new;
		}
	}
}

void	ft_lstadd_back_list(t_list **lst, t_list *new)
{
	t_list	*p;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			p = ft_lstlast_list(*lst);
			p->next = new;
		}
	}
}

t_cmd	*lst_new_cmd(char *cmd, int type, int quote, int is)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->str = ft_strdup(cmd);
	new->quote = quote;
	new->type = type;
	new->is = is;
	new->next = NULL;
	return (new);
}

t_env	*lst_new_env(char *e, int is)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->e = ft_strdup(e);
	new->is = is;
	new->next = NULL;
	return (new);
}

t_list	*lst_new_list(char *cmd, char **args, int in, int out)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->args = args;
	new->in = in;
	new->out = out;
	if (new->in == -2 || new->out == -2)
		new->is = 1;
	else
		new->is = 0;
	new->next = NULL;
	return (new);
}
