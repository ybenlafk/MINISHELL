/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/19 15:26:18 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/04 19:34:56 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lst_len(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type != SPACE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**join_args(t_cmd **cmd)
{
	t_var	p;

	p.i = 0;
	p.str = (char **)malloc((lst_len(*cmd) * sizeof(char *)) + 1);
	if (!p.str)
		return (NULL);
	while ((*cmd) && (*cmd)->type != PIPE)
	{
		if ((*cmd)->type != SPACE)
			p.str[p.i++] = ft_strdup((*cmd)->str);
		(*cmd) = (*cmd)->next;
	}
	p.str[p.i] = NULL;
	return (p.str);
}

int	parser(t_cmd *cmd, t_list *list)
{
	t_var	p;

	p.lst = list;
	p.tmp = cmd;
	while (p.tmp)
	{
		p.str = join_args(&p.tmp);
		if (!p.str)
			return (1);
		p.lst->cmd = ft_strdup(p.str[0]);
		p.lst->args = p.str;
		if (p.tmp)
			p.tmp = p.tmp->next;
		if (p.lst)
			p.lst = p.lst->next;
	}
	return (0);
}
