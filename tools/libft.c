/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:40:25 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/20 16:32:00 by ybenlafk         ###   ########.fr       */
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
static void	freedom(char **p, int i)
{
	while (i >= 0)
	{
		free(p[i]);
		i--;
	}
	free(p);
}

static int	words(char const *s, char c)
{
	int	state;
	int	count;
	int	i;

	state = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			state = 0;
		else if (state == 0)
		{
			state = 1;
			count++;
		}
	i++;
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	res;

	res = 0;
	while (s[res] && s[res] != c)
		res++;
	return (res);
}

static char	**add(char **p, char const *s, char c, int size)
{
	int	i[3];

	i[1] = 0;
	while (i[1] < size)
	{
		i[0] = 0;
		while (*s && (*s == c))
			s++;
		i[2] = word_len(s, c);
		p[i[1]] = (char *)malloc(i[2] + 1);
		if (!p[i[1]])
			return (NULL);
		while (i[2]--)
		{
			p[i[1]][i[0]] = s[i[0]];
			i[0]++;
		}
		p[i[1]][i[0]] = '\0';
		while (*s && *s != c)
			s++;
		i[1]++;
	}
	p[i[1]] = 0;
	return (p);
}

char	**ft_split(char const	*s, char c)
{
	char	**p;
	int		size;

	if (!s)
		return (NULL);
	size = words(s, c);
	p = (char **)malloc((size + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	add(p, s, c, size);
	if (!p)
	{
		freedom(p, size);
		return (NULL);
	}
	return (p);
}

static int	nb_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_strrev(char *str)
{
	int		i;
	int		l;
	char	tmp;

	i = 0;
	l = len(str) - 1;
	while (l > i)
	{
		tmp = str[i];
		str[i] = str[l];
		str[l] = tmp;
		i++;
		l--;
	}
	return (str);
}

static char	*cases(int n, char *s)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	if (n == 0)
	{
		s[0] = '0';
		s[1] = '\0';
		return (s);
	}
	if (n < 0)
	{
		flag = 1;
		n = -n;
	}
	while (n)
	{
		s[j++] = (n % 10) + '0';
		n /= 10;
	}
	if (flag)
		s[j++] = '-';
	s[j] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = nb_len(n);
	s = (char *)malloc(i + 1);
	if (!s)
		return (0);
	cases(n, s);
	ft_strrev(s);
	return (s);
}

