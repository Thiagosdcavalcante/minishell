/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:11 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/08 16:21:25 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_f(t_tokens_f **head)
{
	t_tokens_f	*temp;
	int			i;

	i = 0;
	while ((*head))
	{
		temp = (*head)->next;
		if ((*head)->args)
		{
			if ((*head)->args)
				free((*head)->args);
		}
		if ((*head))
			free((*head));
		(*head) = temp;
	}
	free ((*head));
}

void	free_tokens(t_tokens **head)
{
	t_tokens	*temp;

	while ((*head) != NULL)
	{
		temp = (*head)->next;
		if ((*head)->str != NULL)
		{
			free((*head)->str);
			(*head)->str = NULL;
		}
		if ((*head))
			free((*head));
		(*head) = temp;
	}
	if ((*head))
		free((*head));
}

void	final_free(t_mini *mini)
{
	if (mini->in_ms)
		free(mini->in_ms);
	if (mini->cmmds != NULL)
		free_tokens(&mini->cmmds);
	if (mini->tree)
		free_tree(mini->tree);
	mini->in_ms = NULL;
}

void	free_tree(t_root_f *root)
{
	int	i;

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
