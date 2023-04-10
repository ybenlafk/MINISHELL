/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:24:02 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/09 21:43:41 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_command(t_list *list, int ind, t_env	**env)
{
	if (ind == 1)
	    cd_cmd(list, env);
	if (ind == 2) 
	    export_cmd(env, list);
	if (ind == 3)
	{
		ft_putstr_fd(pwd_cmd(), list->out);
		ft_putstr_fd("\n", list->out);
	}
	if (ind == 4) 
		echo_cmd(list);  
	if (ind == 5)
	    unset_cmd(list, env);  
	if (ind == 6) 
		env_cmd(list, env);
	if (ind == 7)
		exit_cmd(list);
}
