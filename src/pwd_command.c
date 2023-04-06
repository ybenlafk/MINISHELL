/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:31:38 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/30 16:28:07 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*pwd_cmd()
{
	char *buffer;

	buffer = malloc(1024);
	if(getcwd(buffer, 1024) != NULL)
		return (buffer);
	else
		return (NULL);
}
