/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:39:09 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/07 21:54:19 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>

void	print_cmnt(char *str)
{
	ft_putstr_fd("Minishell> exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" numeric argument required\n", 2);
	exit(255);
}

int	ft_isnum(char	*str)
{
	t_var	p;

	p.j = 1;
	p.i = 0;
	p.str = ft_split(str, ' ');
	if (!p.str)
		return (1);
	if (!p.str[0])
		return (free_all(p.str), 1);
	if ((p.str[0][0] == '-' || p.str[0][0] == '+'))
	{
		if (p.str[0][0] == '-')
			p.j = -1;
		p.i++;
	}
	while (p.str[0][p.i])
	{
		if (!(p.str[0][p.i] >= '0' && p.str[0][p.i] <= '9'))
			return (free_all(p.str), 0);
		p.i++;
	}
	if (!p.str[1] && p.i <= 20)
		return (free_all(p.str), p.j);
	return (free_all(p.str), 0);
}

void	norm_exit_cmd(t_list *lst, char *str)
{
	long long			nb;
	int					s;

	s = ft_isnum(str);
	if (!s)
		print_cmnt(str);
	nb = ft_atoi(str);
	if ((nb > 0 && s == -1) || (nb < 0 && s == 1))
		print_cmnt(str);
	else
	{
		if (lst->args && !lst->args[2])
		{
			ft_putstr_fd("exit\n", 1);
			exit(nb % 256);
		}
		else
		{
			ft_putstr_fd("Minishell>$ exit: too many arguments\n", 2);
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
