/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/30 14:42:50 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_parser(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->cmd && !tmp->is)
		{
			if (!ft_strcmp(tmp->cmd, "env"))
			{
				if (tmp->args[1])
				{
					printf("Minishell: env has no options.\n");
					free(tmp->cmd);
					tmp->cmd = NULL;
					free_all(tmp->args);
					break ;
				}
			}
		}
		tmp = tmp->next;
	}
}

t_cmd	*out_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*res;

	tmp = cmd;
	res = NULL;
	while (tmp)
	{
		if (tmp->type == OUT)
		{
			ft_lstadd_back_cmd(&res, lst_new_cmd(tmp->str, tmp->type,
					tmp->quote));
			if (tmp->next)
				if (tmp->next->type == PIPE)
					tmp = tmp->next;
		}
		else
			ft_lstadd_back_cmd(&res, lst_new_cmd(tmp->str, tmp->type,
					tmp->quote));
		tmp = tmp->next;
	}
	return (list_free(&cmd, ft_lstsize(cmd)), res);
}

t_cmd	*del_err(t_cmd *pev, t_cmd *cmd, int i)
{
	t_cmd	*tmp;
	t_cmd	*tmp1;
	t_cmd	*res;

	tmp = cmd;
	tmp1 = pev;
	res = NULL;
	while (tmp1 && i--)
	{
		ft_lstadd_back_cmd(&res, lst_new_cmd(tmp1->str, tmp1->type,
				tmp1->quote));
		tmp1 = tmp1->next;
	}
	while (tmp)
	{
		ft_lstadd_back_cmd(&res, lst_new_cmd(tmp->str, tmp->type, tmp->quote));
		tmp = tmp->next;
	}
	return (res);
}

int	count_el(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**duplicate(char **list)
{
	t_var	p;

	p.str = malloc(count_el(list) * sizeof(char *) + 1);
	if (!p.str)
		return (NULL);
	p.i = 0;
	while (p.i < count_el(list))
	{
		p.str[p.i] = ft_strdup(list[p.i]);
		if (!p.str[p.i])
			return (free_all(p.str), NULL);
		p.i++;
	}
	p.str[p.i] = NULL;
	return (p.str);
}