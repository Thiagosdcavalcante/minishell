/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:11 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/14 14:57:08 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envs(t_envs *envs)
{
	t_envs	*next;

	while (envs)
	{
		free(envs->envcontent);
		free(envs->envkey);
		next = envs->next;
		free(envs);
		envs = next;
	}
}

static void	clear_matrix(t_tokens *mtx)
{
	t_tokens	*tmp;

	tmp = NULL;
	while (mtx)
	{
		if (!mtx->next)
		{
			free(mtx->str);
			free(mtx);
			break ;
		}
		tmp = mtx;
		mtx = mtx->next;
		if (tmp->str)
			free(tmp->str);
		if (tmp)
			free(tmp);
	}
}

void	final_free(t_mini *mini)
{
	if (mini->in_ms)
		free(mini->in_ms);
	if (mini->cmmds)
		clear_matrix(mini->cmmds);
	mini->in_ms = NULL;
	mini->cmmds = NULL;
}
