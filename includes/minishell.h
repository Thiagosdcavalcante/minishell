/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpiana <erpiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:25:07 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/05 20:28:38 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define TRUE 1
# define FALSE 0
# define EXPORT "export"

typedef struct s_envs
{
	char			*envkey;
	char			*envcontent;
	struct s_envs	*next;
}	t_envs;

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

typedef struct s_root
{
	char			*word;
	int				type;
	struct s_root	*left;
	struct s_root	*right;
}			t_root;

typedef struct s_mini
{
	char		*in_ms;
	t_envs		*envars;
	t_tokens	*cmmds;
	t_tokens_f	*tokens;
}	t_mini;

typedef enum e_type
{
	WORD = 0,
	PIPE,
	GREATER,
	LESSER,
	DOUBLEGREATER,
	DOUBLELESSER,
	CMMND,
	MS_FILE,
	PARAM,
}	t_type;

char		*put_space_ms(char *str);
char		**ms_split(char const *s);
char		**custom_split(char const *s, char c);
int			aux_parse(char letter);
int			size_str(char *str);
int			ft_isspace(char c);
int			reverse_branch(t_tokens *tokens, t_root *root, int type);
int			reverse(t_tokens *tokens, t_root *root, int type);
void		create_branch(t_root *root, t_tokens *tokens);
void		custom_export(char *str, t_envs *envs);
void		final_free(t_mini *mini);
void		free_split(char **split);
void		free_envs(t_envs *envs);
void		print_tree(t_root *root, int nivel);
t_envs		*make_env_nodes(char *str);
t_envs		*get_envs(char **original);
t_tokens	*parse_str(char *str);
t_tokens_f	*create_exec_tokens(t_tokens *head);
t_root		*create_tree(t_tokens *tokens);

#endif
