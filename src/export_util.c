/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:25:13 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/03 16:50:25 by nouahidi         ###   ########.fr       */
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
			ft_lstadd_back_env(&t, lst_new_env(tmp->e, 0));
		tmp = tmp->next;
		j++;
	}
	fenv(lst);
	return (t);
}

void	norm_print(int i, char *str, t_list	*lst)
{
	char	*s2;

	ft_putstr_fd("\"", lst->out);
	i++;
	while (str[i])
	{
		s2 = char_to_str(str[i]);
		ft_putstr_fd(s2, lst->out);
		free(s2);
		i++;
	}
	ft_putstr_fd("\"", lst->out);
}

void	ft_print(char *str, t_list *lst)
{
	int		i;
	char	*s2;

	i = 0;
	while (str[i])
	{
		s2 = char_to_str(str[i]);
		ft_putstr_fd(s2, lst->out);
		free(s2);
		if (str[i] == '=')
		{
			if (!str[i + 1])
			{
				ft_putstr_fd("\"", lst->out);
				ft_putstr_fd("\"", lst->out);
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
