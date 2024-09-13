/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:11 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/12 22:25:03 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens **head)
{
	t_tokens	*temp;

	if (!(*head))
		return ;
	while ((*head) != NULL)
	{
		temp = (*head)->next;
		if ((*head)->str != NULL)
		{
			free((*head)->str);
			(*head)->str = NULL;
		}
		if ((*head))
		{
			free((*head));
			(*head) = NULL;
		}
		(*head) = temp;
	}
}

void	final_free(t_mini *mini)
{
	if (mini->in_ms)
	{
		free(mini->in_ms);
		mini->in_ms = NULL;
	}
	if (mini->cmmds != NULL)
	{
		free_tokens(&mini->cmmds);
		mini->cmmds = NULL;
	}
	if (mini->tree)
	{
		free_tree(&mini->tree);
		mini->tree = NULL;
	}
}

void	free_tree(t_root_f **root_free)
{
	int			i;
	t_root_f	*root;

	if (!*root_free)
		return ;
	root = *root_free;
	if (root->left)
		free_tree(&root->left);
	if (root->right)
		free_tree(&root->right);
	if (root->word)
		free(root->word);
	if (root->n_args)
	{
		i = 0;
		while (root->n_args[i] != NULL)
		{
			free(root->n_args[i]);
			i++;
		}
		free(root->n_args);
	}
	free(root);
	*root_free = NULL;
}
