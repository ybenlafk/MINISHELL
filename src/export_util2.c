/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:32:44 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/10 15:01:51 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_ex(t_env	*env, t_list *lst)
{
	t_env	*t;
	int		i;
	char	quotes;

	quotes = '"';
	i = 0;
	t = env;
	while (t)
	{
		ft_putstr_fd("declare -x ", lst->out);
		ft_print(t->e, lst);
		ft_putstr_fd("\n", lst->out);
		t = t->next;
	}
}

int	check_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] == '+')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, int n)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if ((unsigned char)str1[i] < (unsigned char)str2[i])
			return (-1);
		if ((unsigned char)str1[i] > (unsigned char)str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	return (i);
}
