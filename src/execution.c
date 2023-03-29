/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:24:54 by nouahidi          #+#    #+#             */
/*   Updated: 2023/03/28 23:35:26 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_envcmp(char	*str)
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

char	**path_research(t_env	**env)
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
	return(NULL);
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

void	execution(t_list *list, t_env	**env, char **e)
{
    int fd[2];
	char **tabl;
	char *cmd;
	char *li;
	int i = 0;

	li = malloc(5);
	if (pipe(fd) == -1)
		return ;
	tabl = path_research(env);
	if (srch_cmd(list))
		ft_command(list, srch_cmd(list), env);
	else
	{
		int id = fork();
		if (id == -1)
			return ;
		if (id == 0)
		{
			while (tabl[i])
			{
				cmd = ft_strjoin(tabl[i], "/");
				if (access(ft_strjoin(cmd, list->cmd), X_OK) == 0)
					execve(ft_strjoin(cmd, list->cmd), list->args, e);
				i++;
			}
			printf("cmd not found\n");
		}
		int r;
		waitpid(id, &r, 0);
	}
}
