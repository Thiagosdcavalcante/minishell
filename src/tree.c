/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:29:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/31 18:42:14 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tree(t_root_f *root)
{
	int i;

	if (!root)
		return;
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	if (root->word)
		free(root->word);
	if (root->new_args)
	{
		i = 0;
		while (root->new_args[i] != NULL)
		{
			free(root->new_args[i]);
			i++;
		}
		free(root->new_args);
	}
	free(root);
}

static t_tokens_f	*ft_lstlast_token_f(t_tokens_f *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}

static t_tokens_f *find_operator(t_tokens_f *tokens)
{
	t_tokens_f *last_token;
	t_tokens_f *temp;
	t_tokens_f *pipe_token;

	pipe_token = NULL;
	last_token = ft_lstlast_token_f(tokens);
	temp = last_token->prev;
	while (temp)
	{
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
	return (pipe_token);
}


static int branch_op(t_tokens_f *op_token, t_root_f *root, t_tokens_f *tokens)
{
	t_tokens_f *rest;
	t_tokens_f *temp;
	t_tokens_f *head_r;
	t_tokens_f *head_t;

	if (!op_token)
		return (0);
	rest = op_token->next;
	temp = op_token->prev;
	head_t = temp;
	head_r = rest;
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
	head_r->prev = head_t;
	head_t->next = head_r;
	while (head_t->prev)
		head_t = head_t->prev;
	tokens = head_t;
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
	root->word = ft_strdup(tokens->str);
	root->type = tokens->type;
	root->fd = -1;
	if (tokens->args)
		root->args = tokens->args;
	else
		root->args = NULL;
}

t_root_f	*create_tree(t_tokens_f *tokens)
{
	t_root_f *tree;

	if (!tokens)
		return (NULL);
	tree = (t_root_f *)ft_calloc(1, sizeof(t_root_f));
	if (!tree)
		return (NULL);
	create_branch(tree, tokens);
	return (tree);
}
