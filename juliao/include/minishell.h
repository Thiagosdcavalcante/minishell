/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:12:07 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/16 20:03:01 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>


typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef enum e_token
{
	WORD = 0,
	PIPE = 1,
	GREATER = 2,
	LESSER= 3,
	DOUBLEGREATER = 4,
	DOUBLELESSER = 5,
}	t_token;

typedef struct s_env_list
{
	char				*content;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_root
{
	char				*word;
	int					type;
	int					fd;
	struct s_root	*left;
	struct s_root	*right;
}			t_root;

typedef struct s_tokens
{
	char				*word;
	int					type;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}			t_tokens;

typedef struct s_commands
{
	char				*word;
	struct s_commands	*next;
}			t_commands;

typedef struct s_parser
{
	int					type;
	t_list				*redir;
	t_commands			*commands;
	struct s_parser		*next;
}			t_parser;

typedef struct s_data
{
	int				exit;
	char			**paths;
	t_env_list		*envs;
	t_parser		*parser;
	t_tokens		*tokens;
	t_root			*tree;
	t_list			*heredoc;
}			t_data;

//commands
void		ft_lstadd_back_commands(t_commands **lst, t_commands *new);
t_commands	*ft_lstnew_commands(char *content);

//env
void		ft_lstadd_back_env(t_env_list **lst, t_env_list *new);
t_env_list	*ft_lstnew_env(char *content);
//parser
void		ft_lstadd_back_parser(t_parser **lst, t_parser *new);
t_parser	*ft_lstnew_parser(int type);

t_tokens	*ft_lstlast_token(t_tokens *lst);
void		ft_lstadd_back_tokens(t_tokens **lst, t_tokens *new);
t_tokens	*ft_lstnew_tokens(t_tokens *lst, char *content, int type);

void		ft_env(t_data *data);
void		ft_create_env(t_data *data, char *key, char *value);
void		get_envs(t_data *data, char **envp);

void		get_paths(t_data *data, char **envp);
t_bool		ft_search_var(t_data *data, char *key);
void		ft_export(t_data *data, char *content);
void		ft_update_var(t_data *data, char *key, char *value);
void		ft_unset(t_data *data, char *key);

// exec
char		*path_check(t_data *data, char *command);
void		ft_execute(t_data *data, char *command);
int			init_exec(t_data *data, t_root *root);
int			ft_exec(t_data *data, t_root *root);

//parser
void		init_read(t_data *data, char *input);
int			have_quote(char *input);
void		set_parser(t_data *data, char **input_ok);

// utils gambs parser
int			do_not_have(char *input);
char		*set_spaces(char *input);
char		*set_wild_char(char *input, char wild_char);
char		**remove_wild_char(char **input, char wild_char);
void		free_gambs(char **input);

// errors e frees
void		my_error(t_data *data, int status, char *msg, char *command);
void		ffree(t_data *data);

// testes prints
void		plist(t_data *data, int c);
void		parray(char **arr);
void		ptokens(t_tokens *token, int c);
void 		ft_print_ast(t_root *root, char *branch);
void		print_tree(t_root *root, int nivel);

// arvore
void	set_parser2(t_data *data);//teste
t_root	*create_tree(t_tokens *tokens);
void	create_branch(t_root *root, t_tokens *tokens);
int		reverse_branch(t_tokens *tokens, t_root *root, int type);


//redirect
void	ft_redirect(t_data *data, t_root *root);
void	ft_init_redirect(t_data *data, t_root *root);
// void	ft_heredoc(t_data *data);
char	*ft_heredoc(t_tokens *tokens);
void	ft_check_heredoc(t_tokens *tokens);

#endif
