/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:31:38 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/26 14:32:45 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    pwd_cmd()
{
	char *buffer;

	buffer = malloc(1024);
	if(getcwd(buffer, 1024) != NULL)
		printf("%s\n", buffer);
	else
		printf("Error occurred while getting current working directory\n");
}
