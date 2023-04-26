/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:41:14 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/26 13:22:53 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_lstnew(char *str)
{
	t_env	*t;

	t = malloc(sizeof(t_env));
	if (!t)
		return (NULL);
	t->e = ft_strdup(str);
	t->next = NULL;
	return (t);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*t;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	t = *lst;
	while (t->next != NULL)
		t = t->next;
	t->next = new;
}
