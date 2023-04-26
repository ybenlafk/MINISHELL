/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:24:54 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/26 11:15:08 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit_status(int er)
{
	if (er == 2)
		return (1);
	if (er == 13)
		return (126);
	return (0);
}

void	rslt_excve(int i, t_var *var)
{
	if (i)
	{
		perror("Minishell>$ ");
		g_exit_status = ft_exit_status(errno);
		exit(g_exit_status);
	}
	else
	{
		ft_putstr_fd("Minishell>$ command not found: ", var->lst->out);
		ft_putstr_fd(var->lst->cmd, var->lst->out);
		write (1, "\n", 1);
		g_exit_status = 127;
		exit(g_exit_status);
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
	j = -1;
	while (++j <= i)
		st[j] = str[j];
	st[j] = '\0';
	return (st);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	tab = NULL;
}

void	exec_cmd(t_var *var, char **e)
{
	t_var	p;
	int		i;
	char	*st;

	i = 0;
	st = valid_path(var->str, var->lst->cmd);
	if (ft_strchr(var->lst->cmd, '/') || !st)
	{
		st = get_path(var->lst->cmd);
		if (!access(st, X_OK) || st)
			i++;
		free(st);
		if (chech_directory(var->lst->cmd) == 1)
		{
			ft_putstr_fd("Minishell>$ ", var->lst->out);
			ft_putstr_fd(var->lst->cmd, var->lst->out);
			ft_putstr_fd(": is a directory\n", var->lst->out);
			return ;
		}
		else
			execve(var->lst->cmd, var->lst->args, e);
	}
	else if (st)
	{
		i++;
		if (var->lst->in != 0)
			dup2(var->lst->in, 0);
		if (var->lst->out != 1)
			dup2(var->lst->out, 1);
		p.s = char_join(st, '/');
		execve(ft_strjoin(p.s, var->lst->cmd), var->lst->args, e);
	}
	rslt_excve(i, var);
}

void	norm_exec_childs(t_var *var, t_var *p, t_env **env, char **e)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (var->len_ > 1)
		pipe_cases(var, p);
	else
		if (close(p->fds[1]) == -1 || close(p->fds[0]) == -1)
			exit(errno);
	if (srch_cmd(var->lst) && var->len_ > 1)
	{
		ft_command(var->lst, srch_cmd(var->lst), env);
		exit(errno);
	}
	else
		exec_cmd(var, e);
}

int	exec_childs(t_var *var, t_env **env, char **e)
{
	t_var	p;

	p.i = 0;
	if (pipe(p.fds) == -1)
		exit(errno);
	p.pid = fork();
	if (p.pid == -1)
		exit(errno);
	if (p.pid == 0)
		norm_exec_childs(var, &p, env, e);
	else if (var->len_ > 1)
	{
		if (var->j)
			close(var->stat);
		var->stat = dup(p.fds[0]);
		if (close(p.fds[1]) == -1 || close(p.fds[0]) == -1)
			exit(errno);
	}	
	return (var->j++, p.pid);
}

void	execution(t_list *list, t_env **env, char **e)
{
	t_var	p;
	int		pid;
	int		status;

	p.i = 0;
	p.j = 0;
	p.len = 0;
	p.stat = 0;
	p.len_ = lst_size_list(list);
	p.str = path_research(env);
	if (!p.str)
		p.str = ft_split(" ", ' ');
	p.lst = list;
	if (srch_cmd(p.lst) && p.len_ == 1)
	{
		if (p.lst->cmd)
			ft_command(p.lst, srch_cmd(p.lst), env);
	}
	else
	{
		while (p.lst)
		{
			if (p.lst->cmd)
				pid = exec_childs(&p, env, e);
			p.lst = p.lst->next;
		}
		p.ext_st = waitpid(pid, &status, 0);
		while (wait(&status) != -1)
			WIFEXITED(status);
		g_exit_status = WEXITSTATUS(status);
	}
}
