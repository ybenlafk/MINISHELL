/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:40:25 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/09 21:40:48 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_bzero(void *s, size_t n )
{
	char	*dest;

	dest = (char *)s;
	while (n-- > 0)
		*dest++ = 0;
}

void	*ft_calloc(long count, long size)
{
	char	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, size * count);
	return (p);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	scapes(char *str, int *i)
{
	while (str[*i] == '\t' || str[*i] == '\n'
		|| str[*i] == '\v' || str[*i] == '\f'
		|| str[*i] == '\r' || str[*i] == ' ')
		(*i)++;
}

long long	ft_atoi(const char *st)
{
	long		i;
	long long	r;
	long long	nb;

	r = 1;
	nb = 0;
	i = 0;
	while ((st[i] >= 9 && st[i] <= 13) || st[i] == ' ')
		i++;
	if (st[i] == '+' || st[i] == '-')
	{
		if (st[i] == '-')
			r = -1;
	i++;
	}
	while (st[i] >= '0' && st[i] <= '9')
	{
		nb = (nb * 10) + (st[i] - '0');
		i++;
	}
	return (nb * r);
}
