/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:31:38 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/30 16:59:46 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*pwd_cmd(void)
{
	char	*buffer;

	buffer = malloc(1024);
	if (!buffer)
		return (NULL);
	if (getcwd(buffer, 1024) != NULL)
		return (buffer);
	else
		return (free(buffer), NULL);
}
