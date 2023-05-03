/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:39:09 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/03 14:48:28 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>

void	print_cmnt(char *str)
{
	printf ("-->exit\n");
	printf ("Minishell> exit: %s: numeric argument required\n", str);
	exit(255);
}

int	ft_isnum(char	*str)
{
	int		i;
	int		s;
	char	**tab;

	s = 1;
	i = 0;
	tab = ft_split(str, ' ');
	if (!tab[0])
		return (free_all(tab), 0);
	if ((tab[0][0] == '-' || tab[0][0] == '+'))
	{
		if (tab[0][0] == '-')
			s = -1;
		i++;
	}
	while (tab[0][i])
	{
		if (!(tab[0][i] >= '0' && tab[0][i] <= '9'))
			return (free_all(tab), 0);
		i++;
	}
	if (!tab[1] && i <= 20)
		return (free_all(tab), s);
	return (free_all(tab), 0);
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
