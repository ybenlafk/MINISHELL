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

int	g_exit_status = 0;

void	c_hanndler()
{
	int	flag = 0;
	if (waitpid(-1, NULL, WNOHANG) == 0)
		flag = 1;
	if (!flag)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	fill_env(t_env **env, char **e)
{
	t_var	p;

	p.s = getcwd(NULL, 0);
	p.i = 0;
	if (!e[p.i])
	{
		ft_lstadd_back_env(env, lst_new_env(ft_strjoin(ft_strdup("PWD=") ,p.s)));
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
	free(p.s);
}

void	fenv(t_env **env)
{
	t_env	*p;

	if (env)
	{
		while (*env)
		{
			p = *env;
			*env = p->next;
			free(p);
		}
		p = NULL;
	}
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

void f()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **e)
{
	t_cmd	cmd;
	t_list *list;
	t_env	*env;
	t_var	p;

	(void)ac;
	(void)av;
	// int fd = open("/dev/urandom", O_RDONLY);
	// dup2(fd, 0);
	env = NULL;
	fill_env(&env, e);
	while (1)
	{
		signal(SIGINT, c_hanndler);
		signal(SIGQUIT, SIG_IGN);
		p.s = NULL;
		p.s = 	readline("\e[1;32mMinishell>$ \e[0m");
		if (!p.s)
			return (fenv(&env), flist(&list), printf("\e[1;32mexit\e[0m\n"), 1);
		add_history(p.s);
		list = parsing(&cmd, p, env);
		// while (env)
		// {
		// 	printf("|%s|\n", env->e);
		// 	env = env->next;
		// }
		// exit(0);
		// printf("<-------------------cmds-list------------------------>\n");
		// while (list)
		// {
		// 	int i = 0;
		// 	printf("cmd : |%s|\n", list->cmd);
		// 	if (list->args)
		// 		while (list->args[i])
		// 			printf("arg : {%s}\n", list->args[i++]);
		// 	printf("in : |%d|\n", list->in);
		// 	printf("out : |%d|\n", list->out);
		// 	printf("<<<<<<----------------->>>>>>\n");
		// 	list = list->next;
		// }
		// if (list)
		// 	execution(list, &env, e);
		flist(&list);
		free(p.s);
	}
	fenv(&env);
	return (0);
}
