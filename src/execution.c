/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:24:54 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/03 15:33:33 by ybenlafk         ###   ########.fr       */
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
		ft_putstr_fd(" command not found\n", 2);
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

void	exec_cmd(t_var *var, t_env *env)
{
	t_var	p;
	int		i;
	char	*st;
	char	*s1;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	i = 0;
	s1 = NULL;
	st = valid_path(var->str, var->lst->cmd);
	if (!var->lst->cmd[0])
	{
		free(st);
		ft_putstr_fd("Minishell>$ : command not found\n", 2);
		exit(127);
	}
	if (ft_strchr(var->lst->cmd, '/') || !st)
	{
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
	}
	else if (st)
	{
		i++;
		if (var->lst->in != 0)
			dup2(var->lst->in, 0);
		if (var->lst->out != 1)
			dup2(var->lst->out, 1);
		p.s = char_join(ft_strdup(st), '/');
		free(st);
		s1 = ft_strjoin(p.s, var->lst->cmd);
		execve(s1, var->lst->args, env_geter(env));
	}
	rslt_excve(i, var);
}

void	norm_exec_childs(t_var *var, t_var *p, t_env **env)
{
	if (var->len_ > 1)
		pipe_cases(var, p);
	else
		if (close(p->fds[1]) == -1 || close(p->fds[0]) == -1)
			exit(errno);
	if (srch_cmd(var->lst) && var->len_ > 1)
	{
		if (var->lst->cmd && !var->lst->is)
			ft_command(var->lst, srch_cmd(var->lst), env);
		exit(g_var.g_exit_status);
	}
	else
	{
		if (var->lst->cmd && !var->lst->is)
			exec_cmd(var, *env);
		else
			exit(errno);
	}
}

int	exec_childs(t_var *var, t_env **env, char **e)
{
	t_var	p;

	p.i = 0;
	(void)e;
	if (pipe(p.fds) == -1)
		exit(errno);
	p.pid = fork();
	if (p.pid == -1)
		exit(errno);
	if (p.pid == 0)
		norm_exec_childs(var, &p, env);
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
		free_all(p.str);
		if (!p.lst->is && p.lst->cmd)
			ft_command(p.lst, srch_cmd(p.lst), env);
	}
	else
	{
		while (p.lst)
		{
			pid = exec_childs(&p, env, e);
			if (p.lst->in != 0)
				close(p.lst->in);
			if (p.lst->out != 1)
				close(p.lst->out);
			p.lst = p.lst->next;
		}
		p.ext_st = waitpid(pid, &status, 0);
		while (wait(NULL) != -1);
		if (WIFEXITED(status))
			g_var.g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_var.g_exit_status = 128 + WTERMSIG(status);
		free_all(p.str);
	}
	if (g_var.is == 1)
		g_var.g_exit_status = 1;
}
