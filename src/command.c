/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:24:02 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/05/01 10:50:26 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env_pwd(t_env **env)
{
	t_env	*t;

	t = *env;
	while (t)
	{
		if (!ft_strncmp("PWD=", t->e, 4))
			return (t->e);
		t = t->next;
	}
	t = *env;
	while (t)
	{
		if (!ft_strncmp("OLDPWD=", t->e, 7))
			return (t->e);
		t = t->next;
	}
	if (get_home(env))
		return (get_home(env));
	return ("HOME not set");
}

void	ft_command(t_list *list, int ind, t_env	**env)
{
	char	*s;

	s = NULL;
	if (ind == 1)
		cd_cmd(list, env);
	if (ind == 2)
		export_cmd(env, list);
	if (ind == 3)
	{
		s = pwd_cmd();
		if (!s)
			ft_putstr_fd(env_pwd(env) + del_head(env_pwd(env)), list->out);
		ft_putstr_fd(s, list->out);
		ft_putstr_fd("\n", list->out);
		free(s);
	}
	if (ind == 4)
		echo_cmd(list);
	if (ind == 5)
		unset_cmd(list, env);
	if (ind == 6)
		env_cmd(list, env);
	if (ind == 7)
		exit_cmd(list);
}
