/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/04 16:15:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/09 17:36:21 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	len(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char *str;
	int i;

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
	t_cmd *tmp;
	int len;

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
	t_cmd *tmp;

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
	t_env *tmp;

	while (len--)
	{
		tmp = (*philos);
		*philos = (*philos)->next;
		free(tmp);
	}
}

int	env_size(t_env *lst)
{
	t_env *tmp;
	int len;

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
	t_cmd *res;

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
	int *nb;
	char *s;
	char *res;
	int fd;

	nb = malloc(4);
	if (!nb)
		return ("/tmp/tmp-1337");
	fd = open("/dev/urandom", O_RDONLY);
	read(fd, &nb[0], 1);
	read(fd, &nb[1], 1);
	read(fd, &nb[2], 1);
	read(fd, &nb[3], 1);
	s = ft_itoa(*nb);
	res = ft_strjoin(ft_strdup("/tmp/tmp-"), s);
	return (close(fd), free(nb), free(s), res);
}
// Clear any node thats have (null) in cmd and args : type {t_list}.
t_list	*unused_clear(t_list *list)
{
	t_list *res;
	t_list *tmp;

	res = NULL;
	tmp = list;
	while (tmp)
	{
		if (tmp->cmd)
			ft_lstadd_back_list(&res, lst_new_list(tmp->cmd, tmp->args, tmp->in,
						tmp->out));
		tmp = tmp->next;
	}
	return (res);
}
// created a linked list where each node represente a command : type {t_list}
t_list	*create_list(t_cmd *cmd)
{
	t_var p;
	t_list *res;

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
	t_var p;
	t_cmd *res;

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
	t_var p;

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

t_cmd	*del_cmd(t_cmd **lst, char *str)
{
	t_cmd *t;
	t_cmd *tmp;

	tmp = *lst;
	t = NULL;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->str) != 0)
			ft_lstadd_back_cmd(&t, lst_new_cmd(tmp->str, tmp->type,
						tmp->quote));
		tmp = tmp->next;
	}
	return (t);
}

int	i_var(char *s)
{
	int i;

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

char	**del_null(char **str)
{
	t_var p;

	p.i = 0;
	p.len = 0;
	while (str[p.i])
		if (ft_strcmp(str[p.i++], ""))
			p.len++;
	p.str = malloc(sizeof(char *) * p.len + 1);
	if (!p.str)
		return (NULL);
	p.i = 0;
	p.j = 0;
	while (str[p.i])
	{
		if (ft_strcmp(str[p.i], ""))
			p.str[p.j++] = ft_strdup(str[p.i]);
		p.i++;
	}
	p.str[p.j] = NULL;
	return (free_all(str), p.str);
}

int	is_empty(t_list *tmp)
{
	t_var p;

	p.i = 1;
	p.len = 0;
	while (tmp->args[p.i])
	{
		if (tmp->args[p.i][0] != 0)
			p.len++;
		p.i++;
	}
	tmp->args = del_null(tmp->args);
	return (p.len);
}

void	i_valid_arg(t_list *tmp, t_var *p)
{
	while (tmp->args[p->i])
	{
		if (i_var(tmp->args[p->i]))
		{
			p->l = 1;
			printf("export: `%s': not a valid identifier\n", tmp->args[p->i]);
			free(tmp->args[p->i]);
			tmp->args[p->i] = ft_strdup("");
		}
		p->i++;
	}
}

void	export_parser(t_list **list)
{
	t_list *tmp;
	t_var p;

	tmp = *list;
	p.j = 0;
	while (tmp)
	{
		p.i = 1;
		if (tmp->cmd && !tmp->is)
		{
			p.l = 0;
			if (!ft_strcmp(tmp->cmd, "export"))
				i_valid_arg(tmp, &p);
			if (!is_empty(tmp) && p.l)
			{
				free(tmp->cmd);
				free_all(tmp->args);
				tmp->cmd = NULL;
			}
		}
		tmp = tmp->next;
	}
	gvar.is = p.l;
}

void	env_parser(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->cmd && !tmp->is)
		{
			if (!ft_strcmp(tmp->cmd, "env"))
			{
				if (tmp->args[1])
				{
					printf("Minishell: env has no options.\n");
					free(tmp->cmd);
					tmp->cmd = NULL;
					free_all(tmp->args);
					break ;
				}
			}
		}
		tmp = tmp->next;
	}
}

t_cmd	*out_pipe(t_cmd *cmd)
{
	t_cmd *tmp;
	t_cmd *res;

	tmp = cmd;
	res = NULL;
	while (tmp)
	{
		if (tmp->type == OUT)
		{
			ft_lstadd_back_cmd(&res, lst_new_cmd(tmp->str, tmp->type,
						tmp->quote));
			if (tmp->next)
				if (tmp->next->type == PIPE)
					tmp = tmp->next;
		}
		else
			ft_lstadd_back_cmd(&res, lst_new_cmd(tmp->str, tmp->type,
						tmp->quote));
		tmp = tmp->next;
	}
	return (list_free(&cmd, ft_lstsize(cmd)), res);
}

t_cmd	*del_err(t_cmd *pev, t_cmd *cmd, int i)
{
	t_cmd *tmp;
	t_cmd *tmp1;
	t_cmd *res;

	tmp = cmd;
	tmp1 = pev;
	res = NULL;
	// printf (">>%d\n", i--);
	while (tmp1 && i--)
	{
		ft_lstadd_back_cmd(&res, lst_new_cmd(tmp1->str, tmp1->type, tmp1->quote));
		tmp1 = tmp1->next;
	}
	while (tmp)
	{
		ft_lstadd_back_cmd(&res, lst_new_cmd(tmp->str, tmp->type, tmp->quote));
		tmp = tmp->next;
	}
	return (res);
}
