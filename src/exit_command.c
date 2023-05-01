/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:39:09 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/01 20:39:20 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>

void	print_cmnt(char *str)
{
	printf ("Minishell> exit: %s: numeric argument required\n", str);
	exit(255);
}

int	ft_isnum(char	*str)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(str, ' ');
	if (!tab[0])
		return (0);
	if ((tab[0][0] == '-' || tab[0][0] == '+'))
		i++;
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

void	norm_exit_cmd(t_list *lst, char *str)
{
	long long	nb;

	if (!ft_isnum(str))
		print_cmnt(str);
	nb = ft_atoi(str);
	// printf("%lld", nb);
	if (nb <= LONG_MIN || nb >= LONG_MAX)
		print_cmnt(str);
	else
	{
		if (lst->args && !lst->args[2])
		{
			ft_putstr_fd("exit\n", lst->out);
			exit(nb % 256);
		}
		else
		{
			ft_putstr_fd("Minishell>$ exit: too many arguments\n", lst->out);
			g_var.g_exit_status = 1;
		}
	}
}

void	exit_cmd(t_list *lst)
{
	int			i;

	i = 0;
	if (lst->args && lst->args[1])
		norm_exit_cmd(lst, lst->args[1]);
	else
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}
