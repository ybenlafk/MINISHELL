/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 02:53:27 by nouahidi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/06 22:41:15 by nouahidi         ###   ########.fr       */
=======
/*   Updated: 2023/04/08 18:03:11 by ybenlafk         ###   ########.fr       */
>>>>>>> a3fa437a3d4e169733f69a87db63082b70b07c00
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
		printf ("%s\n", pwd_cmd());  
	if (ind == 4) 
		echo_cmd(list);  
	if (ind == 5)
	    unset_cmd(list, env);  
	if (ind == 6) 
		env_cmd(list, env);
	if (ind == 7)
		exit_cmd(list);
}
