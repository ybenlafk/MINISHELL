/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:31:13 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/28 18:12:17 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_var(char *str, t_env *env)
{
	int		i;
	t_env	*t;
	
	i = 1;
	t = env;
	while (t)
	{
		if (ft_strlen_var(str) == ft_strlen_var(t->e))
		{
			if (ft_strncmp(str, t->e, ft_strlen_var(str)) == 0)
				return (i);
		}
		i++;
		t = t->next;
	}
	return (0);
}

void	del_var(int i, t_env **env)
{
	int		j;
	t_env	*t;

	j = 1;
	t = *env;
	while (t)
	{
		if (j == i)
		{
			*env = ft_lstdelone(env, t->e);
		}
		t = t->next;
		j++;
	}
}

void	unset_cmd(t_list *lst, t_env **env)
{
	int	i;
	
	i = 1;
	while (lst->args[i])
	{
		if (search_var(lst->args[i], *env))
			del_var(search_var(lst->args[i], *env), env);
		i++;
	}
}