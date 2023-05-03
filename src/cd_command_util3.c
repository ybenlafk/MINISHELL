/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_util3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:08:50 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/03 15:09:30 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	chech_directory(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) != 0)
		return (0);
	if (S_ISDIR(file_info.st_mode))
		return (1);
	if (S_ISREG(file_info.st_mode))
		return (2);
	return (0);
}
