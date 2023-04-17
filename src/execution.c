/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:24:54 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/11 16:26:33 by nouahidi         ###   ########.fr       */
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

int	lst_size_list(t_list *list)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	pipe_cases(t_var *var, t_var *p)
{
	if (var->j && !var->lst->next)
	{
		dup2(var->stat, 0);
		if (close(p->fds[1]) == -1 || close(p->fds[0]) == -1)
			exit(errno);
	}
	else
	{
		dup2(p->fds[1], 1);
		dup2(var->stat, 0);
		if (close(p->fds[1]) == -1 || close(p->fds[0]) == -1)
			exit(errno);
	}
}

char	*valid_path(char	**tab, char *str)
{
	int		i;
	char	*st;

	i = 0;
	if (!tab[0])
		return (NULL);
	while (tab[i])
	{
		st = char_join(tab[i], '/');
		if (access(ft_strjoin(st, str), X_OK) == 0)
			return (tab[i]);
		i++;
	}
	return (NULL);
}
char	*ft_strchr(const char *str, int s)
{
	int		i;

	i = 0;
	while (str[i] != (char)s)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)str + i);
}

void	rslt_excve(int i, t_var *var)
{
	if (i)
	{
		puts("here");
		perror("Minishell>$ ");
		exit(0);
	}
	else
	{
		write (1,"Minishell>$ command not found: ",32);
		ft_putstr_fd(var->lst->cmd, var->lst->out);
		write (1,"\n",1);
		exit(0);
	}
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
		if (st)
			i++;
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
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (var->len_ > 1)
			pipe_cases(var, &p);
		else
			if (close(p.fds[1]) == -1 || close(p.fds[0]) == -1)
				exit(errno);
		if (srch_cmd(var->lst) && var->len_ > 1)
		{
			if (var->lst->cmd)
				ft_command(var->lst, srch_cmd(var->lst), env);
			exit(errno);
		}
		else
			if (var->lst->cmd)
				exec_cmd(var, e);
	}
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
		ft_command(p.lst, srch_cmd(p.lst), env);
	else
	{
		while (p.lst)
		{
			pid = exec_childs(&p, env, e);
			p.lst = p.lst->next;
		}
		p.ext_st = waitpid(pid, NULL, 0);
		while (wait(NULL) != -1)
			;
	}
}
