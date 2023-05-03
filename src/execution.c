/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:24:54 by nouahidi          #+#    #+#             */
/*   Updated: 2023/05/03 16:20:38 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_var *var, t_env *env)
{
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
		i = norm_exec_cmd(env, var);
	else if (st)
		i = norm_exec_cmd_1(env, var, st);
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

int	exec_childs(t_var *var, t_env **env)
{
	t_var	p;

	p.i = 0;
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

void	exe_norm(t_var *p, t_env **env)
{
	p->status = 0;
	while (p->lst)
	{
		p->pid = exec_childs(p, env);
		if (p->lst->in != 0)
			close(p->lst->in);
		if (p->lst->out != 1)
			close(p->lst->out);
		p->lst = p->lst->next;
	}
	p->ext_st = waitpid(p->pid, &p->status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(p->status))
		g_var.g_exit_status = WEXITSTATUS(p->status);
	else if (WIFSIGNALED(p->status))
		g_var.g_exit_status = 128 + WTERMSIG(p->status);
	free_all(p->str);
}

void	execution(t_list *list, t_env **env)
{
	t_var	p;

	p.i = 0;
	p.pid = 0;
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
		exe_norm(&p, env);
	if (g_var.is == 1)
		g_var.g_exit_status = 1;
}
