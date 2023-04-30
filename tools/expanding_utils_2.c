/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/12 14:18:21 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 16:11:28 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	p = (char *)malloc(len(s1) + len(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (free(s1), p);
}

void	free_all(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

t_exp	*ft_lstlast_exp(t_exp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_exp(t_exp **lst, t_exp *new)
{
	t_exp	*p;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			p = ft_lstlast_exp(*lst);
			p->next = new;
		}
	}
}

t_exp	*lst_new_exp(char *value, int stat)
{
	t_exp	*new;

	new = malloc(sizeof(t_exp));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->stat = stat;
	new->next = NULL;
	return (new);
}
