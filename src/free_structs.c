/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:44:18 by tsantana          #+#    #+#             */
/*   Updated: 2024/05/29 18:00:01 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	clear_matrix(t_matrix *mtx)
{
	t_matrix	*tmp;

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
	t_matrix	*temp;

	temp = mini->cmmds;
	if (mini->in_ms)
		free(mini->in_ms);
	if (mini->cmmds)
		clear_matrix(mini->cmmds);
}
