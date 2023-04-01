/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 02:53:27 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/30 13:29:15 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_command(t_list *list, int ind, t_env **env)
{
	if (ind == 1)
		cd_cmd(list);
	if (ind == 2)
		export_cmd(env, list);
	if (ind == 3)
		pwd_cmd(list);
	if (ind == 4)
		echo_cmd(list);
	if (ind == 5)
		unset_cmd(list, env);
	if (ind == 6)
		env_cmd(list, *env);
	// if (ind == 7)
	//     exit_cmd();
}
