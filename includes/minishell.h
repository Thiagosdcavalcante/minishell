/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpiana <erpiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:25:07 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/13 21:41:01 by tsantana         ###   ########.fr       */
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

typedef struct s_root_f
{
	char				*word;
	int					type;
	int					fd;
	char				**args;
	struct s_root_f	*left;
	struct s_root_f	*right;
}			t_root_f;

typedef struct s_mini
{
	char		*in_ms;
	t_envs		*envars;
	t_tokens	*cmmds;
	t_tokens_f	*tokens;
	t_root_f	*tree;
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
int			aux_parse(char letter);
int			size_str(char *str);
int			ft_isspace(char c);
void		custom_export(char *str, t_envs *envs);
void		final_free(t_mini *mini);
void		free_split(char **split);
void		free_envs(t_envs *envs);
void		ft_check_heredoc(t_mini *data, t_tokens_f *tokens);
t_envs		*make_env_nodes(char *str);
t_envs		*get_envs(char **original);
t_tokens	*parse_str(char *str);
t_tokens_f	*exec_tokens(t_tokens *tkn);
t_tokens_f	*add_special_character(t_tokens **tkn);
t_root_f	*create_tree(t_tokens_f *tokens);

#endif
