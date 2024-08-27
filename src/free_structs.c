/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:11 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/27 19:46:29 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	free_envs(t_envs *envs) */
/* { */
/* 	t_envs	*next; */
/**/
/* 	while (envs) */
/* 	{ */
/* 		free(envs->envcontent); */
/* 		free(envs->envkey); */
/* 		next = envs->next; */
/* 		free(envs); */
/* 		envs = next; */
/* 	} */
/* } */


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
	t_tokens_f *temp;

	while (head != NULL) {
		temp = head;
		head = head->next;
		// if (temp->str)
		// 	free(temp->str);
		if (temp->args) {
			for (int i = 0; temp->args[i] != NULL; i++) {
				free(temp->args[i]);
			}
			free(temp->args);
		}
		free(temp);
	}
}

void	free_tokens(t_tokens *head)
{
	t_tokens *temp;

	while (head != NULL) {
		temp = head;
		head = head->next;
		// if (temp->str)
		// 	free(temp->str);
		free(temp);
	}
}

// static void	clear_matrix(t_tokens *mtx)
// {
// 	t_tokens	*tmp;

// 	tmp = NULL;
// 	while (mtx)
// 	{
// 		if (!mtx->next)
// 		{
// 			free(mtx->str);
// 			free(mtx);
// 			break ;
// 		}
// 		tmp = mtx;
// 		mtx = mtx->next;
// 		if (tmp->str)
// 			free(tmp->str);
// 		if (tmp)
// 			free(tmp);
// 	}
// }

void	final_free(t_mini *mini)
{
	if (mini->in_ms)
		free(mini->in_ms);
	// if (mini->cmmds)
	// 	clear_matrix(mini->cmmds);
	mini->in_ms = NULL;
	mini->cmmds = NULL;
}