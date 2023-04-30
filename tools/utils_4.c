/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/30 16:53:14 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_size(t_env *lst)
{
	t_env	*tmp;
	int		len;

	tmp = lst;
	len = 0;
	if (!tmp)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

t_cmd	*lst_dup(t_cmd *cmd)
{
	t_cmd	*res;

	res = NULL;
	while (cmd)
	{
		ft_lstadd_back_cmd(&res, lst_new_cmd(cmd->str, cmd->type, cmd->quote));
		cmd = cmd->next;
	}
	return (res);
}

char	*generate_name(void)
{
	int		*nb;
	char	*s;
	char	*res;
	int		fd;

	nb = malloc(4);
	if (!nb)
		return ("/tmp/tmp-1337");
	fd = open("/dev/urandom", O_RDONLY);
	read(fd, &nb[0], 1);
	read(fd, &nb[1], 1);
	read(fd, &nb[2], 1);
	read(fd, &nb[3], 1);
	s = ft_itoa(*nb);
	res = ft_strjoin(ft_strdup("/tmp/tmp-"), s);
	return (close(fd), free(nb), free(s), res);
}

t_list	*unused_clear(t_list *list)
{
	t_list	*res;
	t_list	*tmp;
	char	*s[2];

	s[0] = "";
	s[1] = NULL;
	res = NULL;
	tmp = list;
	while (tmp)
	{
		if (tmp->cmd)
		{
			if (tmp->is)
				ft_lstadd_back_list(&res, lst_new_list(NULL, s, tmp->in,
						tmp->out));
			else
				ft_lstadd_back_list(&res, lst_new_list(ft_strdup(tmp->cmd),
						duplicate(tmp->args), tmp->in, tmp->out));
		}
		tmp = tmp->next;
	}
	tmp = list;
	if (ft_lstlast_list(tmp)->is)
		gvar.is = 1;
	return (flist(&list), res);
}

int	pipe_count(t_cmd *cmd)
{
	t_var	p;

	p.i = 0;
	p.tmp = cmd;
	while (p.tmp)
	{
		if (p.tmp->type == PIPE)
			p.i++;
		p.tmp = p.tmp->next;
	}
	return (p.i);
}
