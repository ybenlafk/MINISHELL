/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:47:55 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/28 11:47:01 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_v(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	env_cmd(t_list	*list, t_env **env)
{
	t_env	*t;
	t_env	*new;

	if (!*env)
		return ;
	new = sort_ex(env);
	t = new;
	while (t)
	{
		if (check_v(t->e))
		{
			ft_putstr_fd (t->e, list->out);
			ft_putstr_fd ("\n", list->out);
		}
		t = t->next;
	}
	fenv(&new);
}
