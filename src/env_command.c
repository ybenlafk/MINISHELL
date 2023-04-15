/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:47:55 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/09 21:46:42 by ybenlafk         ###   ########.fr       */
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

	if (!*env)
		return ;
	*env = sort_ex(*env);
	t = *env;
	while (t)
	{
		if (check_v(t->e))
		{
			ft_putstr_fd (t->e, list->out);
			ft_putstr_fd ("\n", list->out);
		}
		t = t->next;
	}
}
