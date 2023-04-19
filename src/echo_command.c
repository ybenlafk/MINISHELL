/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:43:48 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/09 21:45:56 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_args(t_list *list)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (list->args[i])
	{
		if (list->args[i][0] == '-' && list->args[i][1] == 'n')
		{
			j = 1;
			while (list->args[i][j])
			{
				if (list->args[i][j] != 'n')
					return (i);
				j++;
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

void	echo_cmd(t_list *list)
{
	int		i;
	t_list	*t;

	t = list;
	i = check_args(list);
	while (t->args[i])
	{
		ft_putstr_fd (t->args[i], list->out);
		if (t->args[i + 1])
			ft_putstr_fd(" ", list->out);
		i++;
	}
	if (check_args(list) == 1)
		ft_putstr_fd ("\n", list->out);
}
