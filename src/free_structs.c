/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:11 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/26 21:40:04 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_f(t_tokens_f *head)
{
	t_tokens_f	*temp;
	int			i;

	i = 0;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		if (temp->args)
		{
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			if (temp->args)
				free(temp->args);
		}
		if (temp)
			free(temp);
	}
}

void	free_tokens(t_tokens *head)
{
	t_tokens	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		/* if (temp->str) */
		/* 	free(temp->str); */
		if (temp)
			free(temp);
	}
	if (head)
		free(head);
}

void	final_free(t_mini *mini)
{
	if (mini->cmmds != NULL)
		free_tokens(mini->cmmds);
	if (mini->tokens != NULL)
		free_tokens_f(mini->tokens);
	mini->in_ms = NULL;
	mini->cmmds = NULL;
	mini->tokens = NULL;
}
