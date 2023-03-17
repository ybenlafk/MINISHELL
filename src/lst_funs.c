/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 23:20:13 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/16 15:55:15 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lstlast_list(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*p;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			p = ft_lstlast_cmd(*lst);
			p->next = new;
		}
	}
}

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

t_cmd	*lst_new_cmd(char *cmd, int type, int quote)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->str = cmd;
	new->quote = quote;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_env	*lst_new_env(char *e)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->e = e;
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
	new->next = NULL;
	return (new);
}
