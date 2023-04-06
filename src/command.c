/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 02:53:27 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/30 16:28:28 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_command(t_list *list, int ind, t_env	**env, char **tab)
{
	if (ind == 1)
	    cd_cmd(list);
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
