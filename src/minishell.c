/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:59:02 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/21 22:25:18 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	c_hanndler()
// {
// 	// rl_catch_signals = 0;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

void	fill_env(t_env **env, char **e)
{
	int	i;

	i = 0;
	if (!e[i])
	{
		ft_lstadd_back_env(env, lst_new_env("imad"));
		ft_lstadd_back_env(env, lst_new_env("yahya"));
		ft_lstadd_back_env(env, lst_new_env("saad"));
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

int	main(int ac, char **av, char **e)
{
	t_cmd	cmd;
	t_list list;
	t_env	*env;
	char	*output;

	(void)ac;
	(void)av;
	env = NULL;
	// int fd = open("/dev/urandom", O_RDONLY);
	// dup2(fd, 0);
	fill_env(&env, e);
	while (1)
	{
		// signal(SIGINT, c_hanndler);
		signal(SIGQUIT, SIG_IGN);
		output = NULL;
		output = readline("\033[0;34mMinishell>$ ");
		if (!output)
		{
			printf("exit");
			break;
		}
		add_history(output);
		parsing(&cmd, output, env, &list);
		free(output);
	}
	return (0);
}
