/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:29:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/02 21:03:49 by ajuliao-         ###   ########.fr       */
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
	{
		tokens = tokens->next;
	}
	return tokens;
}

static t_tokens_f *find_matching_token(t_tokens_f *tokens, int *types, int num_types)
{
    t_tokens_f *temp;
    int i;

    temp = ft_lstlast_token_f(tokens);
    while (temp)
    {
        i = 0;
        while (i < num_types)
        {
            if (temp->type == types[i])
                return temp;
            i++;
        }
        temp = temp->prev;
    }
    return (NULL);
}

static int setup_branch(t_tokens_f *matching_token, t_tokens_f *tokens, t_root_f *root)
{
    t_tokens_f *rest;

    if (!matching_token)
        return (0);
    rest = matching_token->next;
    if (rest)
        rest->prev = NULL;
    root->word = strdup(matching_token->str);
    root->type = matching_token->type;
    root->args = tokens->args;
    root->fd = -1;
    if (matching_token == tokens)
        tokens = NULL;
    else
        matching_token->prev->next = NULL;
    root->left = create_tree(tokens);
    root->right = create_tree(rest);
    
    return (1);
}
static int reverse_branch(t_tokens_f *tokens, t_root_f *root, int *types, int num_types)
{
    t_tokens_f *matching_token;

    matching_token = find_matching_token(tokens, types, num_types);
    return (setup_branch(matching_token, tokens, root));
}


// static int reverse_branch(t_tokens_f *tokens, t_root_f *root, int *types, int num_types)
// {
//     t_tokens_f *rest;
//     t_tokens_f *last_token;
//     t_tokens_f *temp;
//     int i;

//     last_token = ft_lstlast_token_f(tokens);
//     temp = last_token;

//     while (temp)
//     {
//         i = 0;  // Inicializa o índice para o loop de tipos
//         while (i < num_types)
//         {
//             if (temp->type == types[i])
//             {
//                 rest = temp->next;
//                 if (rest)
//                     rest->prev = NULL;

//                 root->word = strdup(temp->str);
//                 root->type = temp->type;
//                 root->args = tokens->args;
//                 root->fd = -1;

//                 if (temp == tokens)
//                     tokens = NULL;
//                 else
//                     temp->prev->next = NULL;

//                 root->left = create_tree(tokens);
//                 root->right = create_tree(rest);
//                 return (1);
//             }
//             i++;  // Incrementa o índice
//         }
//         temp = temp->prev;
//     }
//     return (0);
// }



static void create_branch(t_root_f *root, t_tokens_f *tokens)
{
    int redirection_types[4] = {GREATER, LESSER, DOUBLEGREATER, DOUBLELESSER};
    int pipe_types[1] = {PIPE};

	if (reverse_branch(tokens, root, pipe_types, 1))
		return ;
    if (reverse_branch(tokens, root, redirection_types, 4))
        return ;
    root->left = NULL;
    root->right = NULL;
    root->word = strdup(tokens->str);
    root->type = tokens->type;
    root->fd = -1;
    root->args = tokens->args;
}



// static int	reverse_branch(t_tokens_f *tokens, t_root_f *root, int type)
// {
// 	t_tokens_f *rest;
// 	t_tokens_f *last_token;
// 	t_tokens_f *temp;
// 	t_tokens_f *temp2;

// 	last_token = ft_lstlast_token_f(tokens);
// 	temp2 = last_token->prev;
// 	while (temp2)
// 	{
// 		if (temp2->type == type)
// 		{
// 			rest = temp2->next;
// 			temp = temp2->prev;
// 			if (temp)
// 				temp->next = NULL;
// 			if (rest)
// 				rest->prev = NULL;
// 			root->word = strdup(temp2->str);
// 			root->type = type;
// 			root->args = (tokens->args);
// 			root->fd = -1;
// 			root->left = create_tree(tokens);
// 			root->right = create_tree(rest);
// 			free(temp2);
// 			return (1);
// 		}
// 		temp2 = temp2->prev;
// 	}
// 	return (0);
// }

// static void	create_branch(t_root_f *root, t_tokens_f *tokens)
// {
// 	if (reverse_branch(tokens, root, PIPE))
// 		return;
//     if (reverse_branch(tokens, root, GREATER) ||
//         reverse_branch(tokens, root, LESSER) ||
//         reverse_branch(tokens, root, DOUBLEGREATER) ||
//         reverse_branch(tokens, root, DOUBLELESSER))
//     {
//         return;
//     }
// 	root->left = NULL;
// 	root->right = NULL;
// 	root->word = strdup(tokens->str);
// 	root->type = tokens->type;
// 	root->fd = -1;
// 	root->args = tokens->args;
// }

t_root_f	*create_tree(t_tokens_f *tokens)
{
	t_root_f *tree;

	if (!tokens)
		return (NULL);
	tree = (t_root_f *)ft_calloc(1, sizeof(t_root_f));
	create_branch(tree, tokens);
	return (tree);
}

// static t_tokens_f	*ft_lstlast_token_f(t_tokens_f *tokens)
// {
// 	while (tokens && tokens->next)
// 		tokens = tokens->next;
// 	return (tokens);
// }

// static t_tokens_f *find_operator(t_tokens_f *tokens)
// {
// 	t_tokens_f *last_token;
// 	t_tokens_f *temp;
// 	t_tokens_f *pipe_token;

// 	pipe_token = NULL;
// 	last_token = ft_lstlast_token_f(tokens);
// 	temp = last_token->prev;
// 	while (temp)
// 	{
// 		if (temp->type == PIPE)
// 		{
// 			pipe_token = temp;
// 			break;
// 		}
// 		else if (temp->type == DOUBLEGREATER || temp->type == DOUBLELESSER ||
// 				temp->type == GREATER || temp->type == LESSER)
// 		{
// 			if (!pipe_token)
// 				pipe_token = temp;
// 		}
// 		temp = temp->prev;
// 	}
// 	return (pipe_token);
// }


// static int branch_op(t_tokens_f *op_token, t_root_f *root, t_tokens_f *tokens)
// {
// 	t_tokens_f *rest;
// 	t_tokens_f *temp;
// 	t_tokens_f *head_r;
// 	t_tokens_f *head_t;

// 	if (!op_token)
// 		return (0);
// 	rest = op_token->next;
// 	temp = op_token->prev;
// 	head_t = temp;
// 	head_r = rest;
// 	if (temp)
// 		temp->next = NULL;
// 	if (rest)
// 		rest->prev = NULL;
// 	root->word = strdup(op_token->str);
// 	root->type = op_token->type;
// 	root->args = tokens->args;
// 	root->fd = -1;
// 	root->left = create_tree(tokens);
// 	root->right = create_tree(rest);
// 	free(op_token);
// 	head_r->prev = head_t;
// 	head_t->next = head_r;
// 	while (head_t->prev)
// 		head_t = head_t->prev;
// 	tokens = head_t;
// 	return (1);
// }

// static void create_branch(t_root_f *root, t_tokens_f *tokens)
// {
// 	t_tokens_f *op_token;

// 	op_token = find_operator(tokens);
// 	if (branch_op(op_token, root, tokens))
// 		return;
// 	root->left = NULL;
// 	root->right = NULL;
// 	root->word = ft_strdup(tokens->str);
// 	root->type = tokens->type;
// 	root->fd = -1;
// 	if (tokens->args)
// 		root->args = tokens->args;
// 	else
// 		root->args = NULL;
// }

// t_root_f	*create_tree(t_tokens_f *tokens)
// {
// 	t_root_f *tree;

// 	if (!tokens)
// 		return (NULL);
// 	tree = (t_root_f *)ft_calloc(1, sizeof(t_root_f));
// 	if (!tree)
// 		return (NULL);
// 	create_branch(tree, tokens);
// 	return (tree);
// }
