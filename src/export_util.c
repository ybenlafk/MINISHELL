/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:25:13 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/26 11:43:16 by nouahidi         ###   ########.fr       */
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

int	ind_str(t_env **lst, char *str)
{
	int		i;
	t_env	*t;

	t = *lst;
	i = 0;
	while (t)
	{
		if (!ft_strcmp(str, t->e))
			return (i);
		i++;
		t = t->next;
	}
	return (i);
}

t_env	*ft_lstdelone(t_env **lst, char	*str)
{
	t_env	*t;
	t_env	*tmp;
	int		i;
	int		j;

	tmp = *lst;
	t = NULL;
	j = 0;
	i = ind_str(lst, str);
	while (tmp)
	{
		if (i != j)
			ft_lstadd_back(&t, ft_lstnew(tmp->e));
		tmp = tmp->next;
		j++;
	}
	return (fenv(lst), t);
}

void	norm_print(int i, char *str, t_list	*lst)
{
	char	quotes;

	quotes = '"';
	ft_putstr_fd(char_to_str(quotes), lst->out);
	i++;
	while (str[i])
		ft_putstr_fd(char_to_str(str[i++]), lst->out);
	ft_putstr_fd(char_to_str(quotes), lst->out);
}

void	ft_print(char *str, t_list *lst)
{
	int		i;
	char	quotes;

	quotes = '"';
	i = 0;
	while (str[i])
	{
		ft_putstr_fd(char_to_str(str[i]), lst->out);
		if (str[i] == '=')
		{
			if (!str[i + 1])
			{
				ft_putstr_fd(char_to_str(quotes), lst->out);
				ft_putstr_fd(char_to_str(quotes), lst->out);
			}
			if (str[i + 1])
			{
				norm_print(i, str, lst);
				i++;
				break ;
			}
		}
		i++;
	}
}
