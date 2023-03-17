/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:40:25 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/13 18:05:49 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strstr(char *str, char *sub)
{
	t_var	p;

	p.len = len(str);
	p.len_ = len(sub);
	p.i = 0;
	p.j = 0;
	while (p.i <= p.len - p.len_)
	{
		while (p.j < p.len_)
		{
			if (str[p.i + p.j] != sub[p.j])
				break ;
			p.j++;
		}
		if (p.j == p.len_)
			return ((char *)&str[p.i]);
		p.i++;
	}
	return (NULL);
}

void	*ft_memmove(void *dst, void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	i = 0;
	if (s == d)
		return (d);
	if (!s && !d)
		return (NULL);
	if (d > s)
		while (len--)
			d[len] = s[len];
	else
		ft_memcpy(d, s, len);
	return (dst);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char *)src;
	b = (unsigned char *)dest;
	if (a || b)
	{
		while (n--)
			*b++ = *a++;
	}
	return (dest);
}