/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:00:55 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 17:46:52 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctl_c(int i)
{
	(void)i;
	close(0);
}

void	is_tty(t_var *p)
{
	int	fd;

	if (!ttyname(0))
	{
		free(p->s);
		fd = open(ttyname(2), O_RDONLY);
		dup2(fd, 0);
		p->fd = -1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putstr_fd("\n", 1);
	}
}
