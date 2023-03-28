/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 02:53:27 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/28 18:11:44 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_command(t_list *list, int ind, t_env	**env)
{
	if (ind == 1)
	    cd_cmd(list);
	if (ind == 2) 
	    export_cmd(env, list);
	if (ind == 3) 
		pwd_cmd();  
	if (ind == 4) 
		echo_cmd(list);  
	if (ind == 5)
	    unset_cmd(list, env);  
	if (ind == 6) 
		env_cmd(list, *env);
	// if (ind == 7) 
	//     exit_cmd();
}
