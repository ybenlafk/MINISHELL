/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:59:02 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/18 16:01:31 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	fill_env(&env, e);
	while (1)
	{
		output = NULL;
		output = readline("\033[0;34mMinishell>$ ");
		if (!output)
			return (0);
		add_history(output);
		parsing(&cmd, output, env, &list);
        // close (3);
		free(output);
	}
	unlink("/tmp/test");
	return (0);
}
