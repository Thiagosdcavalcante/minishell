/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:53:29 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/14 18:58:56 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <termios.h>
# include "libft.h"

typedef struct termios	t_termios;

extern volatile int		g_sig;

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef struct s_env_list
{
	char				*content;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_tokens
{
	char			*str;
	int				type;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}	t_tokens;

typedef struct s_tokens_f
{
	char				*str;
	int					type;
	char				**args;
	struct s_tokens_f	*next;
	struct s_tokens_f	*prev;
}	t_tokens_f;

typedef struct s_root_f
{
	char			*word;
	int				type;
	int				fd;
	char			**args;
	char			**n_args;
	struct s_root_f	*left;
	struct s_root_f	*right;
}			t_root_f;

typedef struct s_mini
{
	int			exit;
	int			status;
	char		**paths;
	char		*in_ms;
	t_env_list	*envs;
	t_tokens	*cmmds;
	t_tokens	*cmmds_order;
	t_tokens_f	*tokens;
	t_root_f	*tree;
	int			fd[2];
}	t_mini;

typedef enum e_type
{
	WORD = 0,
	MS_FILE,
	PIPE,
	GREATER,
	LESSER,
	DOUBLEGREATER,
	DOUBLELESSER,
}	t_type;

char		*put_space_ms(char *str);
char		**ms_split(char const *s);
char		**custom_split(char const *s, char c);
char		**make_word_exec(t_tokens *tkn, int size);
char		*ft_put_zero(void);
char		*full_expansion(t_mini *data, char *arg);
char		*expansion(t_mini *data, char *arg);
char		*get_env(t_mini *data, char *key);
char		*str_heredoc(char *str, t_mini *data);
char		*ft_quotes(char *word);
char		*path_name(void);
char		*get_command_path(t_mini *data, char *cmd);
char		**env_mtx(t_env_list *envs);
int			tokens_checker(t_mini *mini);
int			aux_parse(char letter);
int			size_str(char *str);
int			cond_minishell(t_mini **mini, int cond);
int			ft_redirect(t_mini *data, t_root_f *root);
int			ft_isspace(char c);
int			unlink_here_doc(t_root_f *operator);
int			ft_has_n(char **cmd);
int			ft_exec(t_mini *data, t_root_f *root);
int			init_exec(t_mini *data, t_root_f *root);
int			term_signal(int status);
int			ft_exit(t_mini *data, char **cmd);
int			ft_echo(t_mini *data, t_root_f *root);
int			ft_create_env(t_mini *data, char *key, char *value);
int			get_return_value(int status);
int			ft_create_env(t_mini *data, char *key, char *value);
int			ft_status(pid_t pid);
int			ft_status_whitout_global(pid_t pid);
int			ft_cd(t_mini *data, char **cmd);
int			change(t_mini *data, char *path);
int			ft_env(t_mini *data, char **cmd);
int			ft_export(t_mini *data, char **cmd);
int			is_file(int type);
int			exec_tokens_cond(t_tokens *tkn);
int			n_args(char **args);
int			path_exists(char *path);
int			is_directory(char *path);
int			is_builtins(t_mini *data, t_root_f *root);
int			exec_builtins(t_mini *data, t_root_f *root);
int			verify_if_is_only_one_sinal(t_mini *mini);
int			ft_unset(t_mini *data, char **cmd);
int			ft_strcmp(char *s1, char *s2);
int			check_if_only_spaces(char *str);
int			is_builtins(t_mini *data, t_root_f *root);
int			exec_builtins(t_mini *data, t_root_f *root);
int			sig_heredoc(int sig_heredoc);
int			ft_cd(t_mini *data, char **cmd);
int			ft_check_heredoc(t_mini *data, t_tokens_f *tokens);
int			ft_env(t_mini *data, char **cmd);
int			ft_export(t_mini *data, char **cmd);
int			ft_execute(t_mini *data, char **cmd);
int			return_exit(char *str, int i);
int			n_args(char **args);
int			exec_tokens_cond(t_tokens *tkn);
int			path_exists(char *path);
int			is_directory(char *path);
void		one_quote(char **arg, int *i, char **new_result, char **result);
void		handle_var_exp(t_mini *data, char *arg, int *i, char **result);
void		handle_normal_char(char c, char **result);
void		ft_pwd(t_mini *data, char **cmd);
void		ft_update_var(t_mini *data, char *key, char *value);
void		get_envs(t_mini *data);
void		ft_pipex(t_mini *data, t_root_f *root);
void		sorted_insert(t_env_list **head, t_env_list *node);
void		sort_export(t_env_list *envs);
void		ft_lstadd_back_env(t_env_list **lst, t_env_list *new);
void		get_paths(t_mini *data, char *command);
void		ffree(t_mini *data);
void		ft_init_redirect(t_mini *data, t_root_f *root);
void		my_error(t_mini *data, int status, char *msg, char *command);
void		init_expansion(t_mini *data, char **args, char **n_args);
void		utils_expansion(t_mini *data, char **arg);
void		ft_strcpy(char *dst, const char *src);
void		free_tokens_f(t_tokens_f **head);
void		free_tokens(t_tokens **head);
void		print_list_export(t_env_list *node);
void		init_sig(void);
void		sig_handler(int sig_num);
void		sigint_handler_exec(int sig_num);
void		sigint_handler(int sig_num);
void		first_step(t_mini *mini);
void		free_dup(t_mini *data);
void		print_eof(int i, char *eof);
void		final_free(t_mini *mini);
void		sig_hand_here(int signal);
void		free_split(char **split);
void		free_tree(t_root_f **root);
void		heredoc_util(t_mini *data, char *line, int file, int f);
void		set_sig_func(void);
void		free_paths(t_mini *data);
void		free_dup(t_mini *data);
void		close_fds(int bckp_fd);
void		sig_exec(void);
void		process_reorganization(t_mini *mini);
t_tokens_f	*ft_lstlast_token_f(t_tokens_f *tokens);
t_tokens_f	*token_f_order(t_tokens_f **tkn);
t_tokens	*parse_str(char *str, t_mini *mini);
t_tokens_f	*exec_tokens(t_tokens *tkn);
t_tokens_f	*change_order(t_tokens_f **tkn);
t_tokens_f	*add_special_character(t_tokens **tkn);
t_root_f	*create_tree(t_mini *mini, t_tokens_f *tokens);
t_env_list	*ft_lstnew_env(char *content);
t_tokens_f	*make_exec_token(t_tokens_f **tkn_f, t_tokens **tkn, int word);
t_tokens_f	*rearrange_order(t_tokens_f *tkn);

#endif
