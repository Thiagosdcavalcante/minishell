/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:11 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/03 21:29:12 by ajuliao-         ###   ########.fr       */
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
		// printf("str: %s\n", (*head)->args[0]);
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
	// if (mini->tokens != NULL)
	// 	free_tokens_f(&mini->tokens);
	if (mini->tree)
		free_tree(mini->tree);
	mini->in_ms = NULL;
}

