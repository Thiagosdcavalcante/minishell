/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:29:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/13 21:53:44 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens_f	*ft_lstlast_token_f(t_tokens_f *tokens)
{
	while (tokens && tokens->next)
	{
		tokens = tokens->next;
	}
	return tokens;
}

static int	reverse_branch(t_tokens_f *tokens, t_root_f *root, int type)
{
	t_tokens_f *rest;
	t_tokens_f *last_token;
	t_tokens_f *temp;
	t_tokens_f *temp2;

	last_token = ft_lstlast_token_f(tokens);
	temp2 = last_token->prev;
	while (temp2)
	{
		if (temp2->type == type)
		{
			rest = temp2->next;
			temp = temp2->prev;
			if (temp)
				temp->next = NULL;
			if (rest)
				rest->prev = NULL;
			root->word = strdup(temp2->str);
			root->type = type;
			root->args = (tokens->args);
			root->fd = -1;
			root->left = create_tree(tokens);
			root->right = create_tree(rest);
			free(temp2);
			return (1);
		}
		temp2 = temp2->prev;
	}
	return (0);
}

static void	create_branch(t_root_f *root, t_tokens_f *tokens)
{
	if (reverse_branch(tokens, root, PIPE))
		return;
	if (reverse_branch(tokens, root, GREATER))
		return;
	if (reverse_branch(tokens, root, LESSER))
		return;
	if (reverse_branch(tokens, root, DOUBLEGREATER))
		return;
	if (reverse_branch(tokens, root, DOUBLELESSER))
		return;
	root->left = NULL;
	root->right = NULL;
	root->word = strdup(tokens->str);
	root->type = tokens->type;
	root->fd = -1;
	root->args = tokens->args;
}

t_root_f	*create_tree(t_tokens_f *tokens)
{
	t_root_f *tree;

	if (!tokens)
		return (NULL);
	tree = (t_root_f *)ft_calloc(1, sizeof(t_root_f));
	create_branch(tree, tokens);
	return (tree);
}
