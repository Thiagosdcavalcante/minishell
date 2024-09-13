/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:29:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/12 22:23:27 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	root->word = ft_strdup(m_tkn->str);
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

static void	create_branch(t_mini *mini, t_root_f *root, t_tokens_f *t)
{
	if (r_branch(mini, t, root, PIPE))
		return ;
	if (r_branch(mini, t, root, 3))
		return ;
	root->left = NULL;
	root->right = NULL;
	root->word = full_expansion(mini, t->str);
	root->type = t->type;
	root->fd = -1;
	root->args = t->args;
	root->n_args = NULL;
	if (t->args && t->type < 2)
	{
		root->n_args = (char **)malloc(sizeof(char *) * (n_args(t->args) + 1));
		init_expansion(mini, t->args, root->n_args);
	}
	free(t->args);
	free(t);
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
