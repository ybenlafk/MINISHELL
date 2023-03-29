/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:15:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/28 19:39:23 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc(len(s) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_lstsize(t_cmd *lst)
{
	t_cmd	*tmp;
	int		len;

	tmp = lst;
	len = 0;
	if (!tmp)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

void	list_free(t_cmd **cmd, int len)
{
	t_cmd	*tmp;

	while (len--)
	{
		tmp = (*cmd);
		*cmd = (*cmd)->next;
		free(tmp->str);
		free(tmp);
	}
}

int	ft_isalpha(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	return (0);
}

void	free_env(t_env **philos, int len)
{
	t_env	*tmp;

	while (len--)
	{
		tmp = (*philos);
		*philos = (*philos)->next;
		free(tmp);
	}
}

int	env_size(t_env *lst)
{
	t_env	*tmp;
	int		len;

	tmp = lst;
	len = 0;
	if (!tmp)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
// Duplicate linked list type of {t_cmd}
t_cmd	*lst_dup(t_cmd *cmd)
{
	t_cmd	*res;

	res = NULL;
	while (cmd)
	{
		ft_lstadd_back_cmd(&res, lst_new_cmd(cmd->str, cmd->type, cmd->quote));
		cmd = cmd->next;
	}
	return (res);
}
// Generate filename in /tmp dir for save the heredoc data on it.
char	*generate_name(void)
{
	int		*nb;
	char	*s;
	char	*res;
	int		fd;

	nb = malloc(4);
	if (!nb)
		return ("/tmp/tmp-2343");
	fd = open("/dev/urandom", O_RDONLY);
	read(fd, &nb[0], 1);
	read(fd, &nb[1], 1);
	read(fd, &nb[2], 1);
	read(fd, &nb[3], 1);
	s = ft_itoa(*nb);
	res = ft_strjoin(ft_strdup("/tmp/tmp-"), s);
	return (close(fd), free(s), res);
}
// Clear any node thats have (null) in cmd and args : type {t_list}.
t_list	*unused_clear(t_list *list)
{
	t_list	*res;
	t_list	*tmp;

	res = NULL;
	tmp = list;
	while (tmp)
	{
		if (tmp->cmd && tmp->args)
			ft_lstadd_back_list(&res, lst_new_list(tmp->cmd, tmp->args, tmp->in,
						tmp->out));
		tmp = tmp->next;
	}
	return (res);
}
// created a linked list where each node represente a command : type {t_list}
t_list	*create_list(t_cmd *cmd)
{
	t_var	p;
	t_list	*res;

	p.i = 0;
	res = NULL;
	p.tmp = cmd;
	while (p.tmp)
	{
		if (p.tmp->type == PIPE)
			p.i++;
		p.tmp = p.tmp->next;
	}
	p.i++;
	while (p.i--)
		ft_lstadd_back_list(&res, lst_new_list(NULL, NULL, 0, 0));
	return (res);
}
void	add_new(t_var *p, t_cmd **res)
{
	while (p->tmp)
	{
		if (p->tmp->type == SPACE && p->tmp->next)
		{
			if (p->tmp->next->type == SPACE)
				p->tmp = p->tmp->next;
			else
			{
				ft_lstadd_back_cmd(res, lst_new_cmd(p->tmp->str, p->tmp->type,
							p->tmp->quote));
				p->tmp = p->tmp->next;
			}
		}
		else
		{
			ft_lstadd_back_cmd(res, lst_new_cmd(p->tmp->str, p->tmp->type,
						p->tmp->quote));
			p->tmp = p->tmp->next;
		}
	}
}

t_cmd	*two_to_one(t_cmd *cmd)
{
	t_var	p;
	t_cmd	*res;

	if (!cmd)
		return (NULL);
	p.tmp = cmd;
	res = NULL;
	add_new(&p, &res);
	list_free(&cmd, ft_lstsize(cmd));
	return (res);
}

int	count_fds(t_cmd *cmd, int type, int stat)
{
	t_var	p;

	p.i = 0;
	p.tmp = cmd;
	while (p.tmp && p.tmp->type != PIPE)
	{
		if (!stat)
		{
			if (p.tmp->type == type)
				p.i++;
		}
		else if (p.tmp->type == type || p.tmp->type == APPEND)
			p.i++;
		p.tmp = p.tmp->next;
	}
	return (p.i);
}

int	i_var(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '_' && !ft_isalpha(s[i]))
		return (1);
	i++;
	while (s[i] && s[i] != '=')
	{
		if (s[i + 1])
			if (s[i] == '+' && s[i + 1] == '=')
				break ;
		if (s[i] != '_' && !ft_isalnum(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	export_parser(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!ft_strcmp(tmp->str, "export"))
		{
			tmp = tmp->next;
			if (tmp)
			{
				tmp = tmp->next;
				if (tmp)
				{
					if (i_var(tmp->str))
						return (printf("export: `%s': not a valid identifier\n",
								tmp->str), 1);
				}
				else if (i_var(tmp->str))
					return (1);
			}
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
