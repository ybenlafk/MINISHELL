/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:15:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/26 10:51:33 by ybenlafk         ###   ########.fr       */
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
	int 	*nb;
	char	*s;
	char	*res;

    nb = malloc(4);
    if (!nb)
        return ("/tmp/tmp-2343");
    int fd = open("/dev/urandom", O_RDONLY);
    read(fd, &nb[0], 1);
    read(fd, &nb[1], 1);
    read(fd, &nb[2], 1);
    read(fd, &nb[3], 1);
	s = ft_itoa(*nb);
	res = ft_strjoin(ft_strdup("/tmp/tmp-"), s);
    return (free(s), res);
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