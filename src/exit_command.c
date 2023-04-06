/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:39:09 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/01 16:01:05 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>

void	print_cmnt(char *str)
{
	printf ("Minishell>$ exit: %s: numeric argument required\n", str);
	exit(0);
}

int	ft_isnum(char	*str)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(str, ' ');
	if (!tab[0])
		return (0);
	while (tab[0][i])
	{
		if (!(tab[0][i] >= '0' && tab[0][i] <= '9'))
			return (0);
		i++;
	}
	if (!tab[1])
		return (1);
	return (0);
}

void	exit_cmd(t_list *lst)
{
	int			i;
	long long	nb;

	i = 0;
	if (lst->args[1])
	{
		if (!ft_isnum(lst->args[1]))
			print_cmnt(lst->args[1]);
		nb = ft_atoi(lst->args[1]);
		if (nb <= LONG_MIN && nb >= LONG_MAX)
			print_cmnt(lst->args[1]);
		else
		{
			if (!lst->args[2])
			{
				printf ("exit\n");
				exit(0);
			}
			else
				printf ("Minishell>$ exit: too many arguments\n");
		}
	}
	else
		exit(0);
}
