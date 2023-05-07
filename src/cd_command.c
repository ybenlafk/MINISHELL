/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:24:06 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/06 23:03:45 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	norm_cd2(t_env **env, t_list *lst)
{
	char			*s1;
	char			*s2;

	ft_putstr_fd("cd: error retrieving current ", lst->out);
	ft_putstr_fd("directory: getcwd: cannot access parent ", lst->out);
	ft_putstr_fd("directories: No such file or directory\n", lst->out);
	s1 = get_pwd(env);
	s2 = NULL;
	if (s1)
	{
		s2 = ft_strjoin(ft_strdup(s1), "/..");
		new_pwd(s2, env);
		free(s2);
	}
}

int	norm_cd(t_list	*lst, t_env	**env, char *str)
{
	char			*pwd_path;
	static int		i;
	char			*s1;
	char			*s2;

	if (lst->args && !str && !ft_strcmp("..", lst->args[1]))
	{
		if (i == 0)
		{
			norm_cd2(env, lst);
			return (i = 1, 0);
		}
		else
		{
			i = 0;
			pwd_path = env_pwd(env) + del_head(env_pwd(env));
			if (!new_path(pwd_path))
				return (chdir(getenv("PWD")), 0);
		}
		s2 = pwd_cmd();
		s1 = ft_strjoin(ft_strdup("PWD="), s2);
		new_pwd(s1, env);
		return (free(s1), free(s2), 0);
	}
	return (1);
}

void	norm_cd1(t_env **env)
{
	char			*s1;
	char			*s2;

	ft_putstr_fd("cd: error retrieving current ", 2);
	ft_putstr_fd("directory: getcwd: cannot access parent ", 2);
	ft_putstr_fd("directories: No such file or directory\n", 2);
	s1 = env_pwd(env);
	s2 = NULL;
	if (s1)
	{
		s2 = ft_strjoin(ft_strdup(s1), "/.");
		new_pwd(s2, env);
		free(s2);
	}
}

void	norm_cd_(t_env **env)
{
	char	*s1;
	char	*s2;

	s1 = get_home(env);
	if (chdir(s1) == -1)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		g_var.g_exit_status = 1;
	}
	else
	{
		s2 = ft_strjoin(ft_strdup("PWD="), s1);
		new_pwd(s2, env);
		free(s2);
	}
}

void	cd_cmd(t_list *lst, t_env **env)
{
	t_var	p;

	p.s = pwd_cmd();
	if (lst->args && !lst->args[1])
	{
		free(p.s);
		norm_cd_(env);
		return ;
	}
	if (lst->args && !p.s && !ft_strcmp(".", lst->args[1]))
	{
		norm_cd1(env);
		return ;
	}
	if (!norm_cd(lst, env, p.s))
	{
		free(p.s);
		return ;
	}
	norm_cd_fi(lst, p.s, env);
}
