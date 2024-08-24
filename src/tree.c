/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:29:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/24 18:21:29 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens_f	*ft_lstlast_token_f(t_tokens_f *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return tokens;
}

static t_tokens_f *find_operator(t_tokens_f *tokens)
{
	t_tokens_f *last_token;
	t_tokens_f *temp;
	t_tokens_f *pipe_token = NULL;

	last_token = ft_lstlast_token_f(tokens);
	temp = last_token->prev;
	while (temp) {
		if (temp->type == PIPE)
		{
			pipe_token = temp;
			break;
		}
		else if (temp->type == DOUBLEGREATER || temp->type == DOUBLELESSER ||
		         temp->type == GREATER || temp->type == LESSER)
		{
			if (!pipe_token)
				pipe_token = temp;
		}
		temp = temp->prev;
	}
	return pipe_token;
}


static int branch_op(t_tokens_f *op_token, t_root_f *root, t_tokens_f *tokens)
{
	t_tokens_f *rest;
	t_tokens_f *temp;

	if (!op_token)
		return (0);
	rest = op_token->next;
	temp = op_token->prev;
	if (temp)
		temp->next = NULL;
	if (rest)
		rest->prev = NULL;
	root->word = strdup(op_token->str);
	root->type = op_token->type;
	root->args = tokens->args;
	root->fd = -1;
	root->left = create_tree(tokens);
	root->right = create_tree(rest);
	free(op_token);
	return (1);
}

static void create_branch(t_root_f *root, t_tokens_f *tokens)
{
	t_tokens_f *op_token;

	op_token = find_operator(tokens);
	if (branch_op(op_token, root, tokens))
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