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

t_gvar gvar;

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
	gvar.g_exit_status = 1;
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

void	fenv(t_env **env)
{
	t_env	*p1;
	t_env	*p;

	p1 = *env;
	while (p1)
	{
		free(p1->e);
		p = p1;
		p1 = p1->next;
		free(p);
		p = NULL;
	}
	env = NULL;
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

int	main(int ac, char **av, char **e)
{
	t_cmd	cmd;
	t_list *list;
	t_env	*env;
	t_var	p;

	(void)ac;
	(void)av;
	gvar.g_exit_status = 0;
	gvar.is = 0;
	// int fd = open("/dev/urandom", O_RDONLY);
	// dup2(fd, 0);
	env = NULL;
	fill_env(&env, e);
	while (1)
	{
		signal(SIGINT, c_hanndler);
		signal(SIGQUIT, SIG_IGN);
		p.s = NULL;
		p.s = readline("\e[1;32mMinishell>$ \e[0m");
		if (!p.s)
			return (fenv(&env), flist(&list), printf("\e[1;32mexit\e[0m\n"), gvar.g_exit_status);
		add_history(p.s);
		list = parsing(&cmd, p, env);
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
		if (list)
			execution(list, &env, e);
		flist(&list);
		free(p.s);
	}
	fenv(&env);
	return (0);
}
