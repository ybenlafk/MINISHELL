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
	int	flag;

	flag = 0;
	(void)i;
	if (waitpid(-1, NULL, WNOHANG) == 0)
		flag = 1;
	if (!flag)
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
		ft_lstadd_back_env(env, lst_new_env("OLDPWD"));
		ft_lstadd_back_env(env, lst_new_env(p.s1));
		ft_lstadd_back_env(env, lst_new_env("SHLVL=1"));
		ft_lstadd_back_env(env, lst_new_env("_=/usr/bin/env"));
	}
	else
	{
		while (e[p.i])
		{
			ft_lstadd_back_env(env, lst_new_env(e[p.i]));
			p.i++;
		}
	}
	free(p.s1);
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
			{
				free(p->cmd);
				free_all(p->args);
			}
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
	g_var.g_exit_status = 0;
	g_var.err = 0;
	g_var.is = 0;
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
		// t_list *t = list;
		// printf("<-------------------cmds-list------------------------>\n");
		// while (t)
		// {
		// 	int i = 0;
		// 	printf("cmd : |%s|\n", t->cmd);
		// 	if (t->args)
		// 		while (t->args[i])
		// 			printf("arg : {%s}\n", t->args[i++]);
		// 	printf("in : |%d|\n", t->in);
		// 	printf("out : |%d|\n", t->out);
		// 	printf("is : |%d|\n", t->is);
		// 	printf("<<<<<<----------------->>>>>>\n");
		// 	t = t->next;
		// }
		if (list)
			execution(list, &env, e);
		flist(&list);
		free(p.s);
	}
	fenv(&env);
	return (0);
}
