/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:25:13 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/01 15:33:15 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize_en(t_env *lst)
{
	t_env	*t;
	int		i;

	i = 0;
	t = lst;
	if (!t)
		return (0);
	while (t)
	{
		t = t->next;
		i++;
	}
	return (i);
}

t_env	*ft_lstnew(char *str)
{
	t_env	*t;

	t = malloc(sizeof(t_env));
	if (!t)
		return (NULL);
	t->e = str;
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

t_env	*ft_lstdelone(t_env **lst, char	*str)
{
	t_env	*t;
	t_env	*tmp;

	tmp = *lst;
	t = NULL;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->e) != 0)
			ft_lstadd_back(&t, ft_lstnew(tmp->e));
		tmp = tmp->next;
	}
	return (t);
}

void	ft_print(char *str)
{
	int		i;
	char	quotes;

	quotes = '"';
	i = 0;
	while (str[i])
	{
		printf ("%c", str[i]);
		if (str[i] == '=')
		{
			if (!str[i + 1])
				printf ("%c%c", quotes, quotes);
			if (str[i + 1])
			{
				printf ("%c", quotes);
				i++;
				while (str[i])
					printf ("%c", str[i++]);
				printf ("%c", quotes);
				break ;
			}
		}
		i++;
	}
}
