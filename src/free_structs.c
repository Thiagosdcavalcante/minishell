/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpiana <erpiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:44:18 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/09 15:56:14 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

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

static void	clear_input(t_tokens *mtx)
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

static void	clear_tree(t_root *tree)
{
	t_root	*tmp;

	tmp = NULL;
	while (tree)
	{
		if (!tree->right)
		{
			free(tree->word);
			free(tree);
			break ;
		}
		tmp = tree;
		tree = tree->right;
		if (tmp->word)
			free(tmp->word);
		if (tmp)
			free(tmp);
	}
}

void	final_free(t_mini *mini)
{
	if (mini->in_ms)
		free(mini->in_ms);
	if (mini->cmmds)
		clear_input(mini->cmmds);
	if (mini->tree)
		clear_tree(mini->tree);
	mini->in_ms = NULL;
	mini->cmmds = NULL;
	mini->tree = NULL;
}
