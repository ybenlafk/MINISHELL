/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:59:02 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/28 23:59:08 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	c_hanndler()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	fill_env(t_env **env, char **e)
{
	int	i;

	i = 0;
	if (!e[i])
	{
		// ft_lstadd_back_env(env, lst_new_env("imad"));
		// ft_lstadd_back_env(env, lst_new_env("yahya"));
		// ft_lstadd_back_env(env, lst_new_env("saad"));
	}
	else
	{
		while (e[i])
		{
			ft_lstadd_back_env(env, lst_new_env(e[i]));
			i++;
		}
	}
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
		p.s = readline("\033[1;32mMinishell>$ ");
		if (!p.s)
		{
			printf("exit");
			break;
		}
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
		// fenv(&env);
		if (list)
			execution(list, &env, e);		
		free(p.s);
	}
	return (0);
}
