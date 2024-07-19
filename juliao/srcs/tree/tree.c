/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:17:55 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/13 14:39:14 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	reverse(t_tokens *tokens, t_root *root, int type)
{
	t_tokens	*last_token;

	last_token = ft_lstlast_token(tokens);
	if (tokens == last_token)
		return (0);
	return (1);
}

int	reverse_branch(t_tokens *tokens, t_root *root, int type)
{
	t_tokens	*rest;
	t_tokens	*last_token;
	t_tokens	*temp;
	t_tokens	*temp2;

	last_token = ft_lstlast_token(tokens);
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
			root->word = temp2->word;
			root->type = type;
			root->fd = -1;
			root->left = create_tree(tokens);
			root->right = create_tree(rest);
			free(temp2);
			temp2 = temp;
			return (1);
		}
		temp2 = temp2->prev;
	}
	return (0);
}

void	create_branch(t_root *root, t_tokens *tokens)
{
	int	type;

	type = 1;
	if (reverse_branch(tokens, root, type))
		return ;
	type = 2;
	if (reverse_branch(tokens, root, type))
		return ;
	type = 3;
	if (reverse_branch(tokens, root, type))
		return ;
	type = 4;
	if (reverse_branch(tokens, root, type))
		return ;
	type = 5;
	if (reverse_branch(tokens, root, type))
		return ;
	root->left = NULL;
	root->right = NULL;
	root->word = tokens->word;
	root->type = 0;
	root->fd = -1;
}

t_root	*create_tree(t_tokens *tokens)
{
	t_root	*tree;

	if (!tokens)
		return (NULL);
	tree = ft_calloc(1, sizeof(t_root));
	create_branch(tree, tokens);
	return (tree);
}

void	print_tree(t_root *root, int nivel)
{
	int	i;

	if (root)
	{
		print_tree(root->right, nivel + 1);
		printf("\n\n");
		for(i = 0; i < nivel; i++)
			printf("\t");
		printf("%s - %d", root->word, root->type);
		print_tree(root->left, nivel + 1);
	}
}
