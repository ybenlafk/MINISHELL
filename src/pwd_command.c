/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:31:38 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/31 12:10:23 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    pwd_cmd(t_list *list)
{
	char *buffer;

	if (list->args[1])
	{
		if (list->args[1][0] == '-')
		{
			printf ("Minishell: %s: invalid option\n", list->args[1]);
			return ;
		}
	}
	buffer = malloc(1024);
	if(getcwd(buffer, 1024) != NULL)
		printf("%s\n", buffer);
	else
		printf("Error occurred while getting current working directory\n");
}
