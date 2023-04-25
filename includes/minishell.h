#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <unistd.h>
# include <sys/stat.h>

extern int	g_exit_status;

# define WORD 0
# define HEREDOC 1
# define APPEND 2
# define PIPE 3
# define IN 4
# define OUT 5
# define SPACE 6
# define VAR 7
# define EXIT_ST 8

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
	int				ext_st;
	int				i;
	int				j;
	int				l;
	int				is;
	int				fd;
	int				fds[2];
	int				pid;
	int				len;
	int				len_;
	int				stat;
	char			*file;
	char			*s;
	char			*s1;
	char			*w;
	char			*x;
	char			*ch;
	char			**str;
	int				fd_in;
	int				fd_out;
	t_cmd			*res;
	t_list			*lst;
	t_cmd			*tmp;
	t_exp			*exp;
}					t_var;

void				ft_putstr_fd(char *s, int fd);
void				*ft_calloc(long count, long size);
void				env_parser(t_list **list);
void				export_parser(t_list **list);
int					ft_lstsize_exp(t_exp *lst);
void				free_exp(t_exp **cmd, int len);
t_cmd				*all(t_cmd *cmd, t_list **list);
t_cmd				*two_to_one(t_cmd *cmd);
t_list				*parsing(t_cmd *cmd, t_var p, t_env *env);
t_list				*unused_clear(t_list *list);
t_list				*lst_new_list(char *cmd, char **args, int in, int out);
t_list				*last_lst(t_list *lst);
t_list				*create_list(t_cmd *cmd);
t_cmd				*redire_heredoc(t_cmd *cmd, t_env *env);
t_cmd				*ft_lstlast_cmd(t_cmd *lst);
t_cmd				*lst_dup(t_cmd *cmd);
t_cmd				*lst_join(t_cmd *cmd);
t_cmd				*lst_new_cmd(char *cmd, int type, int quote);
t_exp				*lst_new_exp(char *value, int stat);
t_exp				*ft_lstlast_exp(t_exp *lst);
t_env				*lst_new_env(char *e);
void				rl_replace_line(const char *text, int clear_undo);
void				ft_lstadd_back_exp(t_exp **lst, t_exp *new);
void				free_env(t_env **philos, int len);
t_cmd				*expanding(t_env *env, t_cmd *cmd);
void				list_free(t_cmd **cmd, int len);
void				ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
void				add_special_char(char *s, t_cmd **list_cmd, t_var *p);
void				free_all(char **s);
void				vars_checker(t_var *p, t_cmd **list_cmd, char *s);
void				words_checker(t_var *p, t_cmd **list_cmd, char *s);
void				quotes_expander(t_cmd *cmd, t_env *env);
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
int					count_fds(t_cmd *cmd, int type, int stat);
long long			ft_atoi(const char *str);
int					ft_strcmp(char *s1, char *s2);
int					ft_lstsize(t_cmd *lst);
int					len(char *str);
int					ft_isalnum(int i);
int					ft_isalpha(int i);
int					is_special_char(char c);
int					check_or(char *s, char c);
int					quotes_checker(t_cmd **list_cmd, char *s, t_var *p);
int					sps_skiper(char *s, int *i);
int					redires_checker(t_cmd **list_cmd, char *s, int *i);
int					env_size(t_env *lst);
int					parser(t_cmd *cmd, t_list *list);
int					is_white_sp(char c);
void				cd_cmd(t_list *list, t_env **env);
char				*pwd_cmd(void);
void				echo_cmd(t_list *list);
void				env_cmd(t_list *list, t_env **env);
void				export_cmd(t_env **env, t_list *lst);
int					ft_strlen_var(char *str);
int					ft_strncmp(const char *str1, const char *str2, int n);
t_env				*ft_lstdelone(t_env **lst, char *str);
void				unset_cmd(t_list *lst, t_env **env);
void				execution(t_list *list, t_env **env, char **e);
void				ft_command(t_list *list, int ind, t_env **env);
void				exit_cmd(t_list *lst);
t_env				*sort_ex(t_env *env);
int					ft_lstsize_en(t_env *lst);
t_env				*ft_lstnew(char *str);
t_env				*ft_lstdelone(t_env **lst, char *str);
int					ft_strncmp(const char *str1, const char *str2, int n);
int					ft_strlen(char *str);
char				*del_plus(char *str);
t_env				*sort_ex(t_env *env);
void				add_plus(t_env **env, char *str, int i);
void				ft_lstadd_back(t_env **lst, t_env *new);
void				print_ex(t_env *env, t_list *lst);
void				ft_print(char *str, t_list *lst);
int					check_plus(char *str);
int					check_rot(t_env *env, char *str);
void				add_exp(t_list *lst, t_env **env);
int					norm_exp(t_env **env, char *str, int i);
t_cmd				*del_redires(t_cmd *cmd);
t_cmd				*all(t_cmd *cmd, t_list **list);
void				del_util(t_var *p);
int					drop(t_var *p);
char				*get_home(t_env **env);
char				*env_pwd(t_env **env);
int					del_head(char *str);
int					del_head(char *str);
char				*get_pwd(t_env **env);
int					new_path(char	*str);
char				*del_dr(char *str);
char				*get_home(t_env **env);
char				*new_dr(char *s1, char *s2);
char				*change_dr(char	*str);
void				new_pwd(char *str, t_env **env);
char				*new_pwd_norm(t_env **env, char	*str);
int					check_pwd(t_env **env, char *str);
char				*del_slash(char *str);
void				old_pwd(char *str, t_env **env);
int					lst_size_list(t_list *list);
void				pipe_cases(t_var *var, t_var *p);
char				*ft_strchr(const char *str, int s);
int					ft_envcmp(char	*str);
char				*valid_path(char	**tab, char *str);
char				**path_research(t_env	**env);
int					srch_cmd(t_list *list);
t_env				*ft_lstlast_env(t_env *lst);
t_list				*ft_lstlast_list(t_list *lst);
int					chech_directory(char *path);
void				change_path(t_env **env);
t_cmd				*out_pipe(t_cmd *cmd);

#endif