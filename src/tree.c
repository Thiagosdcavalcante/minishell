/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:29:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/08 16:23:56 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_tokens_f	*find_token(t_tokens_f *tokens, int *types, int num_types)
// {
// 	t_tokens_f	*temp;
// 	int			i;

// 	temp = ft_lstlast_token_f(tokens);
// 	while (temp)
// 	{
// 		i = 0;
// 		while (i < num_types)
// 		{
// 			if (temp->type == types[i])
// 				return (temp);
// 			i++;
// 		}
// 		temp = temp->prev;
// 	}
// 	return (NULL);
// }

static t_tokens_f	*find_token(t_tokens_f *tokens, int t)
{
	t_tokens_f	*temp;
	int			type;

	type = t;
	temp = ft_lstlast_token_f(tokens);
	while (temp)
	{
		if (temp->type == PIPE && type == PIPE)
			return (temp);
		if (temp->type > PIPE && type > PIPE)
			return (temp);
		temp = temp->prev;
	}
	return (NULL);
}

int	branch(t_mini *mini, t_tokens_f *m_tkn, t_tokens_f *tokens, t_root_f *root)
{
	t_tokens_f	*rest;

	if (!m_tkn)
		return (0);
	rest = m_tkn->next;
	if (rest)
		rest->prev = NULL;
	root->word = m_tkn->str;
	root->type = m_tkn->type;
	root->args = tokens->args;
	root->fd = -1;
	if (m_tkn == tokens)
	{
		free(tokens);
		tokens = NULL;
	}
	else
	{
		m_tkn->prev->next = NULL;
		free(m_tkn);
	}
	root->left = create_tree(mini, tokens);
	root->right = create_tree(mini, rest);
	return (1);
}

int	r_branch(t_mini *mini, t_tokens_f *tkn, t_root_f *root, int t)
{
	t_tokens_f	*matching_token;

	matching_token = find_token(tkn, t);
	return (branch(mini, matching_token, tkn, root));
}

static void	create_branch(t_mini *mini, t_root_f *root, t_tokens_f *tokens)
{
	if (r_branch(mini, tokens, root, PIPE))
		return ;
	if (r_branch(mini, tokens, root, 3))
		return ;
	root->left = NULL;
	root->right = NULL;
	root->word = tokens->str;
	root->type = tokens->type;
	root->fd = -1;
	root->args = tokens->args;
	root->new_args = NULL;
	// if (root->word[0] == '$')
	// 	expansion(mini, root->word);
	if (tokens->args && tokens->type < 2)
	{
		root->new_args = (char **)malloc(sizeof(char *) * (n_args(tokens->args) + 1));
		init_expansion(mini, tokens->args, root->new_args);
	}
	free(tokens->args);
	free(tokens);
}

t_root_f	*create_tree(t_mini *mini, t_tokens_f *tokens)
{
	t_root_f	*tree;

	if (!tokens)
		return (NULL);
	tree = (t_root_f *)ft_calloc(1, sizeof(t_root_f));
	create_branch(mini, tree, tokens);
	return (tree);
}
