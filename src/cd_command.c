/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:24:06 by nouahidi          #+#    #+#             */
/*   Updated: 2023/04/02 01:41:26 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*change_dr(char	*str)
{
	int		i;
	int		j;
	char	*st;

	i = 0;
	while (str[i])
		i++;
	j = i;
	while (str[j] != '/' )
		j--;
	j = i - j;
	j = i - j;
	st = malloc(j);
	i = 0;
	while (j > i)
	{
		st[i] = str[i];
		i++;
	}
	st[i] = '\0';
	return (st);
}

char	*new_dr(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, "/");
	str = ft_strjoin(str, s2);
	return (str);
}

void    cd_cmd(t_list   *lst)
{
	char	*str;
	char	**tab;
	int		i;
	int		j;

	i = 0;
	tab = ft_split(lst->args[1], '/');
	str = pwd_cmd();
	if (!lst->args[1])
	{
		chdir("/Users/nouahidi");
		return ;
	}
	while (tab[i])
	{
		if (lst->args[1][0] == '/')
			str = lst->args[1];
		else if (!ft_strcmp(tab[i], ".."))
			str = change_dr(str);
		else if (ft_strcmp(tab[i], "."))
			str = new_dr(str, tab[i]);
		i++;
	}
	printf ("%s\n", str);
	if(chdir(str) != 0)
		printf("Minishell>$ cd: %s: No such file or directory\n", tab[0]);
}
