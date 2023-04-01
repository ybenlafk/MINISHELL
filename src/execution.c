/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:24:54 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/01 17:35:48 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_envcmp(char *str)
{
	char	*st;
	int		i;

	i = 0;
	st = malloc(5);
	st = "PATH";
	while (i < 4)
	{
		if (st[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

char	**path_research(t_env **env)
{
	t_env	*t;
	int		i;

	i = 0;
	t = *env;
	while (t)
	{
		if (ft_envcmp(t->e))
			return (ft_split(t->e + 5, ':'));
		t = t->next;
	}
	return (NULL);
}

int	srch_cmd(t_list *list)
{
	int	i;

	i = 0;
	if (!ft_strcmp(list->cmd, "cd"))
		return (1);
	if (!ft_strcmp(list->cmd, "export"))
		return (2);
	if (!ft_strcmp(list->cmd, "pwd"))
		return (3);
	if (!ft_strcmp(list->cmd, "echo"))
		return (4);
	if (!ft_strcmp(list->cmd, "unset"))
		return (5);
	if (!ft_strcmp(list->cmd, "env"))
		return (6);
	if (!ft_strcmp(list->cmd, "exit"))
		return (7);
	return (0);
}

void	execution(t_list *list, t_env **env, char **e)
{
	t_list	*tmp;
	char	**tabl;
	char	*cmd;
	int		i;
	int		id;
	int		dsa;

	i = 0;
	tabl = path_research(env);
	if (!tabl)
		tabl = ft_split(" ", ' ');
	tmp = list;
	// while (tmp)
	// {
	if (srch_cmd(tmp))
		ft_command(tmp, srch_cmd(tmp), env);
	else
	{
		id = fork();
		if (id == -1)
			return ;
		if (id == 0)
		{
			while (tabl[i])
			{
				cmd = char_join(tabl[i], '/');
				if (access(ft_strjoin(cmd, tmp->cmd), X_OK) == 0)
				{
					if (tmp->in != 0)
						dup2(tmp->in, 0);
					if (tmp->out != 1)
						dup2(tmp->out, 1);
					execve(ft_strjoin(cmd, tmp->cmd), tmp->args, e);
				}
				i++;
			}
			printf("minishell: command not found: %s\n", tmp->cmd);
			exit(errno);
		}
		dsa = 20;
		waitpid(id, &dsa, 0);
	}
	// 	if (tmp->next)
	// 	{
	// 	}
	// 	tmp = tmp->next;
	// }
}
