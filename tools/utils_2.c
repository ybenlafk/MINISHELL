/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:29:23 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/30 14:43:31 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	i_var(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '_' && !ft_isalpha(s[i]))
		return (1);
	i++;
	while (s[i] && s[i] != '=')
	{
		if (s[i + 1])
			if (s[i] == '+' && s[i + 1] == '=')
				break ;
		if (s[i] != '_' && !ft_isalnum(s[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**del_null(char **str)
{
	t_var	p;

	p.i = 0;
	p.len = 0;
	while (str[p.i])
		if (ft_strcmp(str[p.i++], ""))
			p.len++;
	p.str = malloc(sizeof(char *) * p.len + 1);
	if (!p.str)
		return (NULL);
	p.i = 0;
	p.j = 0;
	while (str[p.i])
	{
		if (ft_strcmp(str[p.i], ""))
			p.str[p.j++] = ft_strdup(str[p.i]);
		p.i++;
	}
	p.str[p.j] = NULL;
	return (free_all(str), p.str);
}

int	is_empty(t_list *tmp)
{
	t_var	p;

	p.i = 1;
	p.len = 0;
	while (tmp->args[p.i])
	{
		if (tmp->args[p.i][0] != 0)
			p.len++;
		p.i++;
	}
	tmp->args = del_null(tmp->args);
	return (p.len);
}

void	i_valid_arg(t_list *tmp, t_var *p)
{
	while (tmp->args[p->i])
	{
		if (i_var(tmp->args[p->i]))
		{
			p->l = 1;
			printf("export: `%s': not a valid identifier\n", tmp->args[p->i]);
			free(tmp->args[p->i]);
			tmp->args[p->i] = ft_strdup("");
		}
		p->i++;
	}
}

void	export_parser(t_list **list)
{
	t_list	*tmp;
	t_var	p;

	tmp = *list;
	p.j = 0;
	while (tmp)
	{
		p.i = 1;
		if (tmp->cmd && !tmp->is)
		{
			p.l = 0;
			if (!ft_strcmp(tmp->cmd, "export"))
				i_valid_arg(tmp, &p);
			if (!is_empty(tmp) && p.l)
			{
				free(tmp->cmd);
				free_all(tmp->args);
				tmp->cmd = NULL;
			}
		}
		tmp = tmp->next;
	}
	gvar.is = p.l;
}
