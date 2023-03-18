/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:15:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/18 15:17:17 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc(len(s) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_lstsize(t_cmd *lst)
{
	t_cmd	*tmp;
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

void	list_free(t_cmd **philos, int len)
{
	t_cmd	*tmp;

	while (len--)
	{
		tmp = (*philos);
		*philos = (*philos)->next;
		free(tmp);
	}
}

int	ft_isalpha(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	return (0);
}

void	free_env(t_env **philos, int len)
{
	t_env	*tmp;

	while (len--)
	{
		tmp = (*philos);
		*philos = (*philos)->next;
		free(tmp);
	}
}

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

int	fill_list(t_var *p, t_list **list, int (*add)(t_list **, t_cmd *, int))
{
	int	fd;

	if (p->tmp->next->type == SPACE)
	{
		fd = add(list, p->tmp, 0);
		if (fd < 0)
			return (printf("%s : no such file or directory\n",
						p->tmp->next->next->str), -1);
		if (p->tmp->next->next)
			p->tmp = p->tmp->next->next->next;
	}
	else
	{
		fd = add(list, p->tmp, 1);
		if (fd < 0)
			return (printf("%s : no such file or directory\n",
						p->tmp->next->str), -1);
		if (p->tmp->next)
			p->tmp = p->tmp->next->next;
	}
	return (fd);
}

void	add_new(t_var *p, t_cmd **res)
{
	while (p->tmp)
	{
		if (p->tmp->type == SPACE && p->tmp->next)
		{
			if (p->tmp->next->type == SPACE)
				p->tmp = p->tmp->next;
			else
			{
				ft_lstadd_back_cmd(res, lst_new_cmd(p->tmp->str, p->tmp->type,
							p->tmp->quote, p->tmp->is_added));
				p->tmp = p->tmp->next;
			}
		}
		else
		{
			ft_lstadd_back_cmd(res, lst_new_cmd(p->tmp->str, p->tmp->type,
						p->tmp->quote, p->tmp->is_added));
			p->tmp = p->tmp->next;
		}
	}
}

t_cmd	*two_to_one(t_cmd *cmd)
{
	t_var	p;
	t_cmd	*res;

	if (!cmd)
		return (NULL);
	p.tmp = cmd;
	res = NULL;
	add_new(&p, &res);
	list_free(&cmd, ft_lstsize(cmd));
	return (res);
}

int    is(t_var *p, t_cmd **cmd, int type)
{
    if (!(*cmd)->next)
        return (1);
    if (!(*cmd)->next->next)
        return (1);
    if ((*cmd)->next->next->type == type)
    {
        (*cmd)->is_added = TRUE;
        p->l = 1;
    }
    else if ((*cmd)->next->type == type && !p->l)
        (*cmd)->is_added = TRUE;
    return (0);
}