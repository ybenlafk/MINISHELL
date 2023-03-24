/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:15:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/24 14:16:51 by ybenlafk         ###   ########.fr       */
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

void	list_free(t_cmd **philos, int len)
{
	t_cmd	*tmp;

	while (len--)
	{
		tmp = (*philos);
		*philos = (*philos)->next;
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

char	*generate_name(void)
{
    int *nb;

    nb = malloc(4);
    if (!nb)
        return ("/tmp/tmp-2343");
    return (ft_strjoin(ft_strdup("/tmp/tmp-"), ft_itoa(*nb)));
}

t_list	*unused_clear(t_list *list)
{
	t_list 	*res;
	t_list 	*tmp;

	res = NULL;
	tmp = list;
	while (tmp)
	{
		if (tmp->cmd && tmp->args)
			ft_lstadd_back_list(&res, lst_new_list(tmp->cmd, tmp->args, tmp->in, tmp->out));
		tmp = tmp->next;
	}
	return (res);
}

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
