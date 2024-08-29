/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:11 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/28 21:13:10 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_root_f *root)
{
    if (!root)
        return;
    if (root->left)
        free_tree(root->left);
    if (root->right)
        free_tree(root->right);
    if (root->word)
        free(root->word);
    free(root);
}

void	free_tokens_f(t_tokens_f *head)
{
	t_tokens_f	*temp;
	/* int			i; */

	while (head->next)
	{
		temp = head;
		head = head->next;
		if (temp->args)
		{
			/* i = 0; */
			/* while (temp->args[i]) */
			/* { */
			/* 	if (temp->args[i]) */
			/* 		free(temp->args[i]); */
			/* 	i++; */
			/* } */
			if (temp->args)
				free(temp->args);
		}
		if (temp)
			free(temp);
	}
	free(head);
}

void	free_tokens(t_tokens *head)
{
	t_tokens	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		if (temp->str)
			free(temp->str);
		if (temp)
			free(temp);
	}
	if (head)
		free(head);
}

void	final_free(t_mini *mini)
{
	/* if (mini->tree) */
	/* 	free_tree(mini->tree); */
	if (mini->cmmds != NULL)
		free_tokens(mini->cmmds);
	if (mini->tokens != NULL)
		free_tokens_f(mini->tokens);
}
