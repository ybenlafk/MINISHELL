/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:51:37 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/28 17:24:42 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize_en(t_env *lst)
{
	t_env	*t;
	int		i;

	i = 0;
	t = lst;
	if (!t)
		return (0);
	while (t)
	{
		t = t->next;
		i++;
	}
	return (i);
}

t_env	*ft_lstnew(char *str)
{
	t_env	*t;

	t = malloc(sizeof(t_env));
	if (!t)
		return (NULL);
	t->e = str;
	t->next = NULL;
	return (t);
}
void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*t;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	t = *lst;
	while (t->next != NULL)
		t = t->next;
	t->next = new;
}

t_env	*ft_lstdelone(t_env **lst, char	*str)
{
	t_env	*t;
	t_env	*tmp;

	tmp = *lst;
	t = NULL;
	while(tmp)
	{
		if (ft_strcmp(str, tmp->e) != 0)
			ft_lstadd_back(&t, ft_lstnew(tmp->e));
		tmp = tmp->next;
	}
	return (t);
}


void	print_ex(t_env	*env)
{
	t_env	*t;
	int		i;
	char	quotes;

	quotes = '"';
	i = 0;
	t = env;
	while (t)
	{
		printf ("declare -x ");
		i = 0;
		while (t->e[i])
		{
			printf ("%c", t->e[i]);
			if (t->e[i] == '=')
				printf ("%c", quotes);
			if (!t->e[i + 1])
				printf ("%c", quotes);
			i++;
		}
		printf ("\n");
		t = t->next;
	}
}

int	check_esp(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ' || str[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

int	check_rot(t_env *env, char *str)
{
	t_env	*t;

	t = env;
	while (t)
	{
		if (ft_strcmp(t->e, str) == 0)
			return (0);
		t = t->next;
	}
	return (1);
}

int	ft_strlen_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if(str[i] == '+' && str[i + 1] == '=')
			return (i + 1);
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *str1, const char *str2, int n)
{
	int	i;

	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if ((unsigned char)str1[i + 1] == '+' && (unsigned char)str1[i + 2] == '=')
			return (0);
		if ((unsigned char)str1[i] < (unsigned char)str2[i])
			return (-1);
		if ((unsigned char)str1[i] > (unsigned char)str2[i])
			return (1);
		i++;
	}
	return (0);
}

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
			if (ft_strncmp(str, t->e, ft_strlen_var(str)) == 0)
				return (i);
		}
		t = t->next;
		i++;
	}
	return (0);
}

// void	arg_change(int	i, t_env *env, char *str)
// {
// 	int		j;
// 	t_env	*t;

// 	j = 1;
// 	t = env;
// 	while (t)
// 	{
// 		if (j == i)
// 		{
// 			env = ft_lstdelone(env, t->e);
// 			ft_lstadd_back(&env, ft_lstnew(str));
// 			// while (env)
// 			// {
// 			// 	printf ("%s\n", env->e);
// 			// 	env = env->next;
// 			// }
// 			// exit(0);
// 			break ;
// 		}
// 		j++;
// 		t = t->next;
// 	}
// }

int	check_plus(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			if (str[i - 1] == '+' && str[i - 2] != '+' && str[i - 2] != '-' && str[i - 2] != '/')
				return (1);
		i++;
	}
	return (0);
}

void	add_plus(t_env **env, char *str, int i)
{
	int		j;
	t_env	*t;

	j = 1;
	t = *env;
	while (t)
	{
		if (j == i)
		{
			j = 0;
			while (str[j] != '=' && str[j])
				j++;
			ft_lstadd_back(env, ft_lstnew(ft_strjoin(t->e, str + (j + 1))));
			*env = ft_lstdelone(env, t->e);
			break ;
		}
		t = t->next;
		j++;
	}
}

void	add_exp(t_list	*lst, t_env	**env)
{
	int	i;

	i = 1;
	while (lst->args[i])
	{
		if (!check_esp(lst->args[i]))
		{
			printf ("error\n");
			return ;
		}
		i++;
	}
	i = 1;
	while (lst->args[i])
	{
		if (check_var(lst->args[i], env))
		{
			int		j;
			t_env	*t;
		
			j = 1;
			t = *env;
			while (t)
			{
				if (j == check_var(lst->args[i], env))
				{
					if (check_plus(lst->args[i]))
					{
						add_plus(env, lst->args[i], check_var(lst->args[i], env));
						break ;
					}
					ft_lstadd_back(env, ft_lstnew(lst->args[i]));
					*env = ft_lstdelone(env, t->e);
					break ;
				}
				j++;
				t = t->next;
			}
			i++;
		}
		else
		{
			ft_lstadd_back(env, ft_lstnew(lst->args[i]));
			i++;
		}
	}
}

void	sort_ex(t_env	*env)
{
	t_env	*t;
	t_env	*tp;
	t_env	*tmp;
	t_env	*new;

	t = env;
	tp = env;
	tmp = t;
	new = NULL;
	while (1)
	{
		t = tp;
		tmp = tp;
		while (t)
		{
			if (ft_strcmp(t->e, tmp->e) < 0)
				tmp = t;
			t = t->next;
		}
		ft_lstadd_back(&new, ft_lstnew(tmp->e));
		tp = ft_lstdelone(&tp ,tmp->e);
		if (ft_lstsize_en(new) == ft_lstsize_en(env))
			break ;
	}
	print_ex(new);
}

void	export_cmd(t_env **env, t_list *lst)
{
	int i = 0;

	add_exp(lst, env);
	// sort_ex(env);
}
