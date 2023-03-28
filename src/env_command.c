/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:47:55 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/26 14:49:15 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_cmd(t_list	*list, t_env *env)
{
	int i;
	t_env	*t;

	t = env;
	while (t)
	{
		printf ("%s\n", t->e);
		t = t->next;
	}
}
