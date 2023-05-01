/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/10 17:43:50 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/04/10 15:56:54 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_dilemiter(t_cmd **list_cmd, char *s, int *i)
{
	t_var	p;

	p.i = 0;
	if (sps_skiper(s, i))
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(" ", SPACE, 0, 0));
	while (s[*i] && !is_white_sp(s[*i]) && !is_special_char(s[*i]))
	{
		if (is_quoted(list_cmd, s, &p, i))
			return (1);
		get_dil_util(&p, list_cmd, s, i);
		if (is_quoted(list_cmd, s, &p, i))
			return (1);
	}
	return (0);
}

int	redires_checker(t_cmd **list_cmd, char *s, int *i)
{
	if (!s[*i] || !s[*i + 1])
		return (0);
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd("<<", HEREDOC, 0, 0));
		*i += 2;
		if (get_dilemiter(list_cmd, s, i))
			return (1);
	}
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		ft_lstadd_back_cmd(list_cmd, lst_new_cmd(">>", APPEND, 0, 0));
		*i += 2;
	}
	return (0);
}

char	*char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
