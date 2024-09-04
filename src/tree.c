/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:29:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/03 22:58:55 by ajuliao-         ###   ########.fr       */
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
    // if (root->args)
    // {
    //     i = 0;
    //     while (root->args[i] != NULL)
    //     {
    //         free(root->args[i]);
    //         i++;
    //     }
    //     free(root->args);
    // }

    // free do root->args

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
    root->word = ft_strdup(matching_token->str);
    root->type = matching_token->type;
    root->args = tokens->args;
    root->fd = -1;
    if (matching_token == tokens)
    {
        // free(tokens);
        printf("entrou na condição\n");
        free(matching_token);
    }
    else
    {
        matching_token->prev->next = NULL;
        free(matching_token);
        // free(tokens);
    }
    root->left = create_tree(tokens);
    root->right = create_tree(rest);
    // root->left_token = tokens;
    // root->right_token = rest;
    return (1);
}
static int reverse_branch(t_tokens_f *tokens, t_root_f *root, int *types, int num_types)
{
    t_tokens_f *matching_token;

    matching_token = find_matching_token(tokens, types, num_types);
    return (setup_branch(matching_token, tokens, root));
}

char    **new_args(char **args)
{
    char    **result;
    int     i;

    i = 0;
    result = (char **)malloc(sizeof(char *) * (1 + 1));
    if (!args)
        return (result = NULL);
    while(args[i])
    {
        result[i] = ft_strdup(args[i]);
        i++;
    }
    result[i] = NULL;
    return (result);
}

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
    root->word = ft_strdup(tokens->str);
    root->type = tokens->type;
    root->fd = -1;
    root->args = tokens->args;
    // root->args = new_args(tokens->args);
    // root->args = (char **)malloc(sizeof(char *) * (1 + 1));
    // int i = 0;
    // while (tokens->args && root->args[i] && tokens->args[i])
    // {
        // root->args[i] = ft_strdup(tokens->args[i]);
        // free(tokens->args[i]);
        // i++;
    // }

    // dup do tokens->args
    // free tokens->args
    // free(tokens->args);
    free(tokens);
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
