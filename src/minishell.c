/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:59:02 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 18:16:41 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_gvar	g_var;

void	c_hanndler(int i)
{
	(void)i;
	if (waitpid(-1, NULL, WNOHANG))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_var.g_exit_status = 1;
}

void	fill_env(t_env **env, char **e)
{
	t_var	p;

	p.s = getcwd(NULL, 0);
	p.i = 0;
	if (!e[p.i])
	{
		p.s1 = ft_strjoin(ft_strdup("PWD="), p.s);
		ft_lstadd_back_env(env, lst_new_env("OLDPWD", 0));
		ft_lstadd_back_env(env, lst_new_env(p.s1, 0));
		ft_lstadd_back_env(env, lst_new_env("SHLVL=", 0));
		ft_lstadd_back_env(env, lst_new_env("_=/usr/bin/env", 0));
		free(p.s1);
	}
	else
	{
		while (e[p.i])
		{
			ft_lstadd_back_env(env, lst_new_env(e[p.i], 0));
			p.i++;
		}
	}
	free(p.s);
}

void	flist(t_list **list)
{
	t_list	*p;

	if (list)
	{
		while (*list)
		{
			p = *list;
			*list = p->next;
			if (p->cmd)
				free(p->cmd);
			free_all(p->args);
			free(p);
		}
		p = NULL;
	}
}

int	main_norm(t_var *p, t_env **env, t_list **list)
{
	p->s = NULL;
	p->s = readline("\e[1;32mMinishell>$ \e[0m");
	if (!p->s)
		return (fenv(env), flist(list), printf("\e[1;32mexit\e[0m\n"), 1);
	if (ft_strcmp(p->s, ""))
		add_history(p->s);
	return (0);
}

int	main(int ac, char **av, char **e)
{
	t_cmd	cmd;
	t_list	*list;
	t_env	*env;
	t_var	p;

	(void)ac;
	(void)av;
	glob_init();
	env = NULL;
	list = NULL;
	fill_env(&env, e);
	while (1)
	{
		signal(SIGINT, c_hanndler);
		signal(SIGQUIT, SIG_IGN);
		if (main_norm(&p, &env, &list))
			return (g_var.g_exit_status);
		list = parsing(&cmd, p, env);
		if (list)
			execution(list, &env);
		flist(&list);
		free(p.s);
	}
	fenv(&env);
	return (0);
}
