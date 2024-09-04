/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:53:29 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/03 20:59:29 by tsantana         ###   ########.fr       */
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

extern volatile int	g_sig;

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
	char				*word;
	int					type;
	int					fd;
	char				**args;
	char				**new_args;
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
int			aux_parse(char letter);
int			size_str(char *str);
int			ft_isspace(char c);
int			unlink_here_doc(t_root_f *operator);
int			ft_has_n(char **cmd);
int			ft_exec(t_mini *data, t_root_f *root);
int			init_exec(t_mini *data, t_root_f *root);
int			ft_exit(t_mini *data, char **cmd);
int			ft_echo(t_mini *data, char **cmd);
int			ft_create_env(t_mini *data, char *key, char *value);
int			get_return_value(int status);
void		final_free(t_mini *mini);
void		free_split(char **split);
void		ft_check_heredoc(t_mini *data, t_tokens_f *tokens);
void		one_quote(char **arg, int *i, char **new_result, char **result);
void		handle_var_expansion(t_mini *data, char *arg, int *i, char **result);
void		handle_normal_char(char c, char **result);
void		ft_pwd(t_mini *data, char **cmd);
void		ft_unset(t_mini *data, char **cmd);
void		sig_exec(void);
void		sig_hand_here(int signal);
int			ft_cd(t_mini *data, char **cmd);
int			change(t_mini *data, char *path);
void		ft_update_var(t_mini *data, char *key, char *value);
int			ft_env(t_mini *data, char **cmd);
void		get_envs(t_mini *data);
void		ft_pipex(t_mini *data, t_root_f *root);
void		sorted_insert(t_env_list **head, t_env_list *node);
void		sort_export(t_env_list *envs);
void		ft_lstadd_back_env(t_env_list **lst, t_env_list *new);
void		get_paths(t_mini *data);
void		ffree(t_mini *data);
int			ft_export(t_mini *data, char **cmd);
void		ft_init_redirect(t_mini *data, t_root_f *root);
int			ft_execute(t_mini *data, char **cmd);
void		my_error(t_mini *data, int status, char *msg, char *command);
void		init_expansion(t_mini *data, char **args, char **new_args);
void		utils_expansion(t_mini *data, char **arg);
void		ft_strcpy(char *dst, const char *src);
void		free_tokens_f(t_tokens_f **head);
void		free_tokens(t_tokens **head);
void		print_list_export(t_env_list *node);
void		init_sig(void);
void		sig_handler(int sig_num);
int			ft_redirect(t_mini *data, t_root_f *root);
char		*ft_quotes(char *word);
void		free_tree(t_root_f *root);
t_tokens	*parse_str(char *str);
t_tokens_f	*exec_tokens(t_tokens *tkn);
t_tokens_f	*add_special_character(t_tokens **tkn);
t_root_f	*create_tree(t_tokens_f *tokens);
t_env_list	*ft_lstnew_env(char *content);

#endif
