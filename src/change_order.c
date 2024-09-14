/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:16:40 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/13 17:56:55 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_to_ordered_list(t_tokens **cmmds_order, t_tokens *token)
{
	t_tokens	*new_token;
	t_tokens	*temp;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return ;
	new_token->str = strdup(token->str);
	new_token->type = token->type;
	new_token->next = NULL;
	new_token->prev = NULL;
	if (!*cmmds_order)
		*cmmds_order = new_token;
	else
	{
		temp = *cmmds_order;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
		new_token->prev = temp;
	}
}

void	reorg_group(t_tokens *start, t_tokens *end, t_tokens **cmmds_order)
{
	t_tokens	*current;
	t_tokens	*first_word;

	first_word = NULL;
	current = start;
	while (current && current != end)
	{
		if (current->type == WORD)
		{
			first_word = current;
			break ;
		}
		current = current->next;
	}
	if (first_word)
		add_token_to_ordered_list(cmmds_order, first_word);
	current = start;
	while (current && current != end)
	{
		if (current != first_word && current->type != PIPE)
			add_token_to_ordered_list(cmmds_order, current);
		current = current->next;
	}
	if (end && end->type == PIPE)
		add_token_to_ordered_list(cmmds_order, end);
}

void	reorganize(t_tokens *tokens, t_tokens **cmmds_order)
{
	t_tokens	*current;
	t_tokens	*next_pipe;
	t_tokens	*start_of_group;

	next_pipe = NULL;
	current = tokens;
	while (current)
	{
		start_of_group = current;
		next_pipe = current;
		while (next_pipe && next_pipe->type != PIPE)
			next_pipe = next_pipe->next;
		reorg_group(start_of_group, next_pipe, cmmds_order);
		if (next_pipe)
			current = next_pipe->next;
		else
			current = NULL;
	}
}

void	process_reorganization(t_mini *mini)
{
	mini->cmmds_order = NULL;
	reorganize(mini->cmmds, &mini->cmmds_order);
}

int	unlink_here_doc(t_root_f *root)
{
	if (root == NULL)
		return (0);
	if (root->type == DOUBLELESSER)
	{
		if (root->right && root->right->word)
		{
			if (unlink(root->right->word) == -1)
			{
				perror("Error unlinking file");
				return (-1);
			}
		}
	}
	if (root->left)
		unlink_here_doc(root->left);
	if (root->right)
		unlink_here_doc(root->right);
	return (0);
}
