/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:24:06 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/26 14:25:56 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    cd_cmd(t_list   *list)
{
	char *new_directory = "/Users/nouahidi/Desktop";
	if(chdir(new_directory) == 0) {
		printf("Directory changed to %s\n", new_directory);
	} else {
		printf("Error occurred while changing directory\n");
	}
}