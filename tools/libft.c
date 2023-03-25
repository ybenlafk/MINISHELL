/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:40:25 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/25 14:32:38 by ybenlafk         ###   ########.fr       */
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

int	ft_isalnum(int i)
{
	if ((i >= '0' && i <= '9') || (i >= 'a' && i <= 'z') || (i >= 'A'
			&& i <= 'Z') || i == '_')
		return (1);
	return (0);
}