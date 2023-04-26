/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:51:37 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/26 14:18:37 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var(char *str, t_env **env)
{
	t_env	*t;
	int		i;
	int		j;

	t = *env;
	i = 1;
	while (t)
	{
		if (ft_strlen_var(str) == ft_strlen_var(t->e))
		{
			if (!ft_strncmp(str, t->e, ft_strlen_var(str)))
				return (i);
		}
		t = t->next;
		i++;
	}
	return (0);
}

int	check_empty_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	norm_exp(t_env	**env, char *str, int i)
{
	int		j;
	t_env	*t;

	j = 1;
	t = *env;
	while (t && check_empty_var(str))
	{
		if (j == check_var(str, env))
		{
			if (check_plus(str))
			{
				add_plus(env, str, check_var(str, env));
				break ;
			}
			ft_lstadd_back(env, ft_lstnew(str));
			ft_lstdelone(env, t->e);
			break ;
		}
		j++;
		t = t->next;
	}
	i++;
	return (i);
}

void	add_exp(t_list	*lst, t_env	**env)
{
	int		i;
	char	*str;
	int		j;

	i = 1;
	while (lst->args[i])
	{
		if (check_var(lst->args[i], env))
			i = norm_exp(env, lst->args[i], i);
		else
		{
			str = del_plus(lst->args[i]);
			ft_lstadd_back(env, ft_lstnew(str));
			free(str);
			i++;
		}
	}
}

void	export_cmd(t_env **env, t_list *lst)
{
	t_env	*new;

	if (!*env)
		return ;
	if (lst->args[1])
		add_exp(lst, env);
	else
	{
		new = sort_ex(*env);
		print_ex(new, lst);
	}
}
