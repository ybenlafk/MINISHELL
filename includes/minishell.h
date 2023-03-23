/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:30:01 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/23 14:57:07 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1
# define WORD 0
# define HEREDOC 1
# define APPEND 2
# define PIPE 3
# define IN 4
# define OUT 5
# define SPACE 6
# define VAR 7

typedef struct array
{
	char			*cmd;
	char			**args;
	int				in;
	int				out;
	struct array	*next;
}					t_list;

typedef struct list
{
	char			*str;
	int				type;
	int				quote;
	int				is_added;
	struct list		*next;
}					t_cmd;

typedef struct env
{
	char			*e;
	struct env		*next;
}					t_env;

typedef struct exp
{
	char			*value;
	int				stat;
	struct exp		*next;
}					t_exp;

typedef struct var
{
	int				i;
	int				j;
	int				l;
	int				is;
	int				fd;
	int				len;
	int				len_;
	int				stat;
	char			*file;
	char			*s;
	char			*s1;
	char			*ch;
	char			**str;
	int				fd_in;
	int				fd_out;
	t_cmd			*res;
	t_list			*lst;
	t_cmd			*tmp;
	t_exp			*exp;
}					t_var;

t_cmd				*all(t_cmd *cmd, t_list **list);
t_list				*parsing(t_cmd *cmd, t_var p, t_env *env);
t_list				*unused_clear(t_list *list);
t_list				*lst_new_list(char *cmd, char **args, int in, int out);
t_list				*last_lst(t_list *lst);
t_list				*create_list(t_cmd *cmd);
t_cmd				*redire_heredoc(t_cmd *cmd, t_env *env, char *file);
t_cmd				*ft_lstlast_cmd(t_cmd *lst);
t_cmd				*lst_dup(t_cmd *cmd);
t_cmd				*lst_join(t_cmd *cmd);
t_cmd				*lst_new_cmd(char *cmd, int type, int quote, int is_added);
t_exp				*lst_new_exp(char *value, int stat);
t_exp				*ft_lstlast_exp(t_exp *lst);
t_env				*lst_new_env(char *e);
void				rl_replace_line(const char *text, int clear_undo);
void				ft_lstadd_back_exp(t_exp **lst, t_exp *new);
void				free_env(t_env **philos, int len);
void				expanding(t_env *env, t_cmd *cmd);
void				list_free(t_cmd **philos, int len);
void				ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
void				add_special_char(char c1, char c2, t_cmd **list_cmd,
						t_var *p);
void				vars_checker(t_var *p, t_cmd **list_cmd, char *s);
void				words_checker(t_var *p, t_cmd **list_cmd, char *s);
void				quotes_expander(t_var *p, t_cmd *cmd, t_env *env);
void				lexer_pro_max(t_exp **exp, char *s, t_var *p);
void				error(char *e);
void				ft_lstadd_back_list(t_list **lst, t_list *new);
char				*ft_strdup(char *s);
char				*char_to_str(char c);
char				*s_quote_trim(char *str);
char				*d_quote_trim(char *str);
char				*char_to_str(char c);
char				*is_quotes(char *s, int *i, int stat);
char				*char_join(char *str, char c);
char				*set_value(t_env *env, char *rep);
char				*ft_strjoin(char *s1, char *s2);
char				*check_set(t_exp *exp, t_env *env);
char				*syntax_checker(t_cmd *cmd, char *str);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*generate_name(void);
int					ft_strcmp(char *s1, char *s2);
int					ft_lstsize(t_cmd *lst);
int					len(char *str);
int					ft_isalnum(int i);
int					ft_isalpha(int i);
int					is_special_char(char c);
int					redires_checker(t_cmd **list_cmd, char c1, char c2, int *i);
int					check_or(char *s, char c);
int					quotes_checker(t_cmd **list_cmd, char *s, t_var *p);
int					sps_skiper(char *s, int *i);
int					redires_checker(t_cmd **list_cmd, char c1, char c2, int *i);
int					env_size(t_env *lst);
int					parser(t_cmd *cmd, t_list *list);

#endif