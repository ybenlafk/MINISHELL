/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:47:55 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/28 23:37:43 by ybenlafk         ###   ########.fr       */
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
