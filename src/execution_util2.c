/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:18:58 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/03 16:20:08 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit_status(int er)
{
	if (er == 2)
		return (127);
	if (er == 13)
		return (126);
	return (0);
}

void	rslt_excve(int i, t_var *var)
{
	(void)var;
	if (i)
	{
		perror("Minishell> ");
		g_var.g_exit_status = ft_exit_status(errno);
		exit(g_var.g_exit_status);
	}
	else
	{
		ft_putstr_fd("Minishell>$ : command not found\n", 2);
		g_var.g_exit_status = 127;
		exit(g_var.g_exit_status);
	}
}

char	*get_path(char *str)
{
	int		i;
	int		j;
	char	*st;

	i = ft_strlen(str);
	i--;
	while (i >= 0)
	{
		if (str[i] == '/')
			break ;
		i--;
	}
	if (str[i] != '/')
		return (NULL);
	st = malloc(i);
	if (!st)
		return (NULL);
	j = -1;
	while (++j <= i)
		st[j] = str[j];
	st[j] = '\0';
	return (st);
}

int	norm_exec_cmd(t_env *env, t_var *var)
{
	int		i;
	char	*st;

	i = 0;
	st = get_path(var->lst->cmd);
	if (!access(st, X_OK) || st)
		i++;
	free(st);
	if (chech_directory(var->lst->cmd) == 1)
	{
		ft_putstr_fd("Minishell> ", 2);
		ft_putstr_fd(var->lst->cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	else
		execve(var->lst->cmd, var->lst->args, env_geter(env));
	return (i);
}

int	norm_exec_cmd_1(t_env *env, t_var *var, char	*st)
{
	char	*s1;
	char	*s2;
	int		i;

	i = 1;
	if (var->lst->in != 0)
		dup2(var->lst->in, 0);
	if (var->lst->out != 1)
		dup2(var->lst->out, 1);
	s2 = char_join(ft_strdup(st), '/');
	free(st);
	s1 = ft_strjoin(s2, var->lst->cmd);
	execve(s1, var->lst->args, env_geter(env));
	return (i);
}
